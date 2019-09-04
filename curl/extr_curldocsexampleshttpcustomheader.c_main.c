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
struct curl_slist {int dummy; } ;
typedef  int /*<<< orphan*/  CURLcode ;
typedef  int /*<<< orphan*/  CURL ;

/* Variables and functions */
 int /*<<< orphan*/  CURLE_OK ; 
 int /*<<< orphan*/  CURLOPT_HTTPHEADER ; 
 int /*<<< orphan*/  CURLOPT_URL ; 
 int /*<<< orphan*/  CURLOPT_VERBOSE ; 
 int /*<<< orphan*/  curl_easy_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * curl_easy_init () ; 
 int /*<<< orphan*/  curl_easy_perform (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  curl_easy_setopt (int /*<<< orphan*/ *,int /*<<< orphan*/ ,...) ; 
 char* curl_easy_strerror (int /*<<< orphan*/ ) ; 
 struct curl_slist* curl_slist_append (struct curl_slist*,char*) ; 
 int /*<<< orphan*/  curl_slist_free_all (struct curl_slist*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  stderr ; 

int main(void)
{
  CURL *curl;
  CURLcode res;

  curl = curl_easy_init();
  if(curl) {
    struct curl_slist *chunk = NULL;

    /* Remove a header curl would otherwise add by itself */
    chunk = curl_slist_append(chunk, "Accept:");

    /* Add a custom header */
    chunk = curl_slist_append(chunk, "Another: yes");

    /* Modify a header curl otherwise adds differently */
    chunk = curl_slist_append(chunk, "Host: example.com");

    /* Add a header with "blank" contents to the right of the colon. Note that
       we're then using a semicolon in the string we pass to curl! */
    chunk = curl_slist_append(chunk, "X-silly-header;");

    /* set our custom set of headers */
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, chunk);

    curl_easy_setopt(curl, CURLOPT_URL, "localhost");
    curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

    res = curl_easy_perform(curl);
    /* Check for errors */
    if(res != CURLE_OK)
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));

    /* always cleanup */
    curl_easy_cleanup(curl);

    /* free the custom headers */
    curl_slist_free_all(chunk);
  }
  return 0;
}