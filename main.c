#include <stdio.h>
#include <curl/curl.h>

void main() {
    curl_global_init(CURL_GLOBAL_ALL);
    CURLM *multi = curl_multi_init ();
    CURL *curl = curl_easy_init ();

    curl_easy_setopt (curl, CURLOPT_VERBOSE, 1L);
    curl_easy_setopt (curl, CURLOPT_URL, "http://api.ipify.org");

    curl_multi_add_handle (multi, curl);

    int still_running = 0;
    curl_multi_perform (multi, &still_running);

    int i = 0;

    while (still_running) {
        printf ("%d. Perform\n", i);

        int n;
        curl_multi_wait (multi, NULL, 0, -1, &n);
        printf("%d. Wait %d\n", i, n);

        curl_multi_perform (multi, &still_running);

        i++;
    }

    curl_multi_remove_handle (multi, curl);
    curl_easy_cleanup (curl);
    curl_multi_cleanup (multi);
    curl_global_cleanup ();
}
