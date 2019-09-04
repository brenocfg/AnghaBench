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
typedef  int /*<<< orphan*/  curl_mimepart ;
typedef  int /*<<< orphan*/  curl_mime ;
typedef  int /*<<< orphan*/  CURLM ;
typedef  int /*<<< orphan*/  CURL ;

/* Variables and functions */
 int CURLM_OK ; 
 int /*<<< orphan*/  CURLOPT_HEADER ; 
 int /*<<< orphan*/  CURLOPT_MIMEPOST ; 
 int /*<<< orphan*/  CURLOPT_NOPROGRESS ; 
 int /*<<< orphan*/  CURLOPT_URL ; 
 int /*<<< orphan*/  CURLOPT_USERPWD ; 
 int /*<<< orphan*/  CURLOPT_VERBOSE ; 
 int /*<<< orphan*/  CURLOPT_XFERINFOFUNCTION ; 
 int /*<<< orphan*/  CURL_GLOBAL_ALL ; 
 int /*<<< orphan*/  CURL_ZERO_TERMINATED ; 
 int TEST_ERR_MAJOR_BAD ; 
 int /*<<< orphan*/  TEST_HANG_TIMEOUT ; 
 int /*<<< orphan*/  abort_on_test_timeout () ; 
 int /*<<< orphan*/  curl_easy_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  curl_global_cleanup () ; 
 int /*<<< orphan*/ * curl_mime_addpart (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  curl_mime_data (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  curl_mime_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * curl_mime_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  curl_mime_name (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  curl_multi_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  curl_multi_remove_handle (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int curl_multi_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  easy_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  easy_setopt (int /*<<< orphan*/ *,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  global_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  multi_add_handle (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  multi_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  multi_perform (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int /*<<< orphan*/  start_test_timing () ; 
 long xferinfo ; 

int test(char *URL)
{
  CURL *curls = NULL;
  CURLM *multi = NULL;
  int still_running;
  int i = 0;
  int res = 0;
  curl_mimepart *field = NULL;
  curl_mime *mime = NULL;
  int counter = 1;

  start_test_timing();

  global_init(CURL_GLOBAL_ALL);

  multi_init(multi);

  easy_init(curls);

  mime = curl_mime_init(curls);
  field = curl_mime_addpart(mime);
  curl_mime_name(field, "name");
  curl_mime_data(field, "value", CURL_ZERO_TERMINATED);

  easy_setopt(curls, CURLOPT_URL, URL);
  easy_setopt(curls, CURLOPT_HEADER, 1L);
  easy_setopt(curls, CURLOPT_VERBOSE, 1L);
  easy_setopt(curls, CURLOPT_MIMEPOST, mime);
  easy_setopt(curls, CURLOPT_USERPWD, "u:s");
  easy_setopt(curls, CURLOPT_XFERINFOFUNCTION, xferinfo);
  easy_setopt(curls, CURLOPT_NOPROGRESS, 1L);

  multi_add_handle(multi, curls);

  multi_perform(multi, &still_running);

  abort_on_test_timeout();

  while(still_running && counter--) {
    int num;
    res = curl_multi_wait(multi, NULL, 0, TEST_HANG_TIMEOUT, &num);
    if(res != CURLM_OK) {
      printf("curl_multi_wait() returned %d\n", res);
      res = TEST_ERR_MAJOR_BAD;
      goto test_cleanup;
    }

    abort_on_test_timeout();

    multi_perform(multi, &still_running);

    abort_on_test_timeout();
  }

test_cleanup:

  curl_mime_free(mime);
  curl_multi_remove_handle(multi, curls);
  curl_multi_cleanup(multi);
  curl_easy_cleanup(curls);
  curl_global_cleanup();

  if(res)
    i = res;

  return i; /* return the final return code */
}