#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  CURLcode ;
typedef  int /*<<< orphan*/  CURL ;

/* Variables and functions */
 int /*<<< orphan*/  CURLE_OK ; 
 int /*<<< orphan*/  CURLINFO_REDIRECT_URL ; 
 int /*<<< orphan*/  CURLINFO_RESPONSE_CODE ; 
 int /*<<< orphan*/  CURLOPT_URL ; 
 int /*<<< orphan*/  curl_easy_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  curl_easy_getinfo (int /*<<< orphan*/ *,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/ * curl_easy_init () ; 
 int /*<<< orphan*/  curl_easy_perform (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  curl_easy_setopt (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 char* curl_easy_strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  stderr ; 

int main(void)
{
  CURL *curl;
  CURLcode res;
  char *location;
  long response_code;

  curl = curl_easy_init();
  if(curl) {
    curl_easy_setopt(curl, CURLOPT_URL, "https://example.com");

    /* example.com is redirected, figure out the redirection! */

    /* Perform the request, res will get the return code */
    res = curl_easy_perform(curl);
    /* Check for errors */
    if(res != CURLE_OK)
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));
    else {
      res = curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
      if((res == CURLE_OK) &&
         ((response_code / 100) != 3)) {
        /* a redirect implies a 3xx response code */
        fprintf(stderr, "Not a redirect.\n");
      }
      else {
        res = curl_easy_getinfo(curl, CURLINFO_REDIRECT_URL, &location);

        if((res == CURLE_OK) && location) {
          /* This is the new absolute URL that you could redirect to, even if
           * the Location: response header may have been a relative URL. */
          printf("Redirected to: %s\n", location);
        }
      }
    }

    /* always cleanup */
    curl_easy_cleanup(curl);
  }
  return 0;
}