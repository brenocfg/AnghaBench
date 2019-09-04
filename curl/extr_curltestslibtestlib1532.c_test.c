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
typedef  int /*<<< orphan*/  CURL ;

/* Variables and functions */
 int CURLE_HTTP_RETURNED_ERROR ; 
 int CURLE_OK ; 
 int /*<<< orphan*/  CURLINFO_RESPONSE_CODE ; 
 int /*<<< orphan*/  CURLOPT_URL ; 
 int /*<<< orphan*/  CURL_GLOBAL_ALL ; 
 int /*<<< orphan*/  curl_easy_cleanup (int /*<<< orphan*/ *) ; 
 int curl_easy_getinfo (int /*<<< orphan*/ *,int /*<<< orphan*/ ,long*) ; 
 int curl_easy_perform (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  curl_easy_reset (int /*<<< orphan*/ *) ; 
 char* curl_easy_strerror (int) ; 
 int /*<<< orphan*/  curl_global_cleanup () ; 
 int /*<<< orphan*/  easy_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  easy_setopt (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,int,...) ; 
 int /*<<< orphan*/  global_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 

int test(char *URL)
{
  CURL *curl;
  long httpcode;
  int res = CURLE_OK;

  global_init(CURL_GLOBAL_ALL);

  easy_init(curl);

  easy_setopt(curl, CURLOPT_URL, URL);

  res = curl_easy_perform(curl);
  if(res) {
    fprintf(stderr, "%s:%d curl_easy_perform() failed with code %d (%s)\n",
            __FILE__, __LINE__, res, curl_easy_strerror(res));
    goto test_cleanup;
  }

  res = curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &httpcode);
  if(res) {
    fprintf(stderr, "%s:%d curl_easy_getinfo() failed with code %d (%s)\n",
            __FILE__, __LINE__, res, curl_easy_strerror(res));
    goto test_cleanup;
  }
  if(httpcode != 200) {
    fprintf(stderr, "%s:%d unexpected response code %ld\n",
            __FILE__, __LINE__, httpcode);
    res = CURLE_HTTP_RETURNED_ERROR;
    goto test_cleanup;
  }

  /* Test for a regression of github bug 1017 (response code does not reset) */
  curl_easy_reset(curl);

  res = curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &httpcode);
  if(res) {
    fprintf(stderr, "%s:%d curl_easy_getinfo() failed with code %d (%s)\n",
            __FILE__, __LINE__, res, curl_easy_strerror(res));
    goto test_cleanup;
  }
  if(httpcode != 0) {
    fprintf(stderr, "%s:%d curl_easy_reset failed to zero the response code\n"
            "possible regression of github bug 1017\n", __FILE__, __LINE__);
    res = CURLE_HTTP_RETURNED_ERROR;
    goto test_cleanup;
  }

test_cleanup:
  curl_easy_cleanup(curl);
  curl_global_cleanup();
  return res;
}