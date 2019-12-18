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
typedef  int CURLcode ;
typedef  int /*<<< orphan*/  CURL ;

/* Variables and functions */
 int CURLE_OK ; 
 int /*<<< orphan*/  CURLINFO_EFFECTIVE_URL ; 
 int /*<<< orphan*/  CURLINFO_REDIRECT_COUNT ; 
 int /*<<< orphan*/  CURLINFO_REDIRECT_URL ; 
 int /*<<< orphan*/  CURLINFO_RESPONSE_CODE ; 
 int /*<<< orphan*/  CURLOPT_FOLLOWLOCATION ; 
 int /*<<< orphan*/  CURLOPT_URL ; 
 int TEST_ERR_MAJOR_BAD ; 
 int /*<<< orphan*/  curl_easy_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  curl_easy_getinfo (int /*<<< orphan*/ *,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/ * curl_easy_init () ; 
 int curl_easy_perform (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  curl_global_cleanup () ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  printf (char*,int,int,int,char*,char*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  test_setopt (int /*<<< orphan*/ *,int /*<<< orphan*/ ,...) ; 

int test(char *URL)
{
  CURL *curl;
  CURLcode res = CURLE_OK;
  long curlResponseCode;
  long curlRedirectCount;
  char *effectiveUrl = NULL;
  char *redirectUrl = NULL;

  curl = curl_easy_init();
  if(!curl) {
    fprintf(stderr, "curl_easy_init() failed\n");
    curl_global_cleanup();
    return TEST_ERR_MAJOR_BAD;
  }

  test_setopt(curl, CURLOPT_URL, URL);
  /* just to make it explicit and visible in this test: */
  test_setopt(curl, CURLOPT_FOLLOWLOCATION, 0L);

  /* Perform the request, res will get the return code */
  res = curl_easy_perform(curl);

  curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &curlResponseCode);
  curl_easy_getinfo(curl, CURLINFO_REDIRECT_COUNT, &curlRedirectCount);
  curl_easy_getinfo(curl, CURLINFO_EFFECTIVE_URL, &effectiveUrl);
  curl_easy_getinfo(curl, CURLINFO_REDIRECT_URL, &redirectUrl);

  printf("res: %d\n"
         "status: %d\n"
         "redirects: %d\n"
         "effectiveurl: %s\n"
         "redirecturl: %s\n",
         (int)res,
         (int)curlResponseCode,
         (int)curlRedirectCount,
         effectiveUrl,
         redirectUrl);

test_cleanup:

  /* always cleanup */
  curl_easy_cleanup(curl);
  curl_global_cleanup();

  return res;
}