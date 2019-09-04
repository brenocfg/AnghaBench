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
typedef  scalar_t__ CURLMcode ;
typedef  int /*<<< orphan*/  CURLM ;
typedef  int /*<<< orphan*/  CURL ;

/* Variables and functions */
 scalar_t__ CURLM_OK ; 
 int /*<<< orphan*/  CURLOPT_INFILESIZE ; 
 int /*<<< orphan*/  CURLOPT_SSH_PRIVATE_KEYFILE ; 
 int /*<<< orphan*/  CURLOPT_SSH_PUBLIC_KEYFILE ; 
 int /*<<< orphan*/  CURLOPT_UPLOAD ; 
 int /*<<< orphan*/  CURLOPT_URL ; 
 int /*<<< orphan*/  CURLOPT_USERPWD ; 
 int /*<<< orphan*/  CURLOPT_VERBOSE ; 
 int /*<<< orphan*/  CURL_GLOBAL_ALL ; 
 int /*<<< orphan*/  curl_easy_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  curl_global_cleanup () ; 
 int /*<<< orphan*/  curl_multi_cleanup (int /*<<< orphan*/ *) ; 
 scalar_t__ curl_multi_remove_handle (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  easy_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  easy_setopt (int /*<<< orphan*/ *,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  global_init (int /*<<< orphan*/ ) ; 
 long libtest_arg2 ; 
 int /*<<< orphan*/  multi_add_handle (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  multi_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  multi_perform (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  stderr ; 

int test(char *URL)
{
  int stillRunning;
  CURLM *multiHandle = NULL;
  CURL *curl = NULL;
  CURLMcode res = CURLM_OK;

  global_init(CURL_GLOBAL_ALL);

  multi_init(multiHandle);

  easy_init(curl);

  easy_setopt(curl, CURLOPT_USERPWD, libtest_arg2);
  easy_setopt(curl, CURLOPT_SSH_PUBLIC_KEYFILE, "curl_client_key.pub");
  easy_setopt(curl, CURLOPT_SSH_PRIVATE_KEYFILE, "curl_client_key");

  easy_setopt(curl, CURLOPT_UPLOAD, 1L);
  easy_setopt(curl, CURLOPT_VERBOSE, 1L);

  easy_setopt(curl, CURLOPT_URL, URL);
  easy_setopt(curl, CURLOPT_INFILESIZE, (long)5);

  multi_add_handle(multiHandle, curl);

  /* this tests if removing an easy handle immediately after multi
     perform has been called succeeds or not. */

  fprintf(stderr, "curl_multi_perform()...\n");

  multi_perform(multiHandle, &stillRunning);

  fprintf(stderr, "curl_multi_perform() succeeded\n");

  fprintf(stderr, "curl_multi_remove_handle()...\n");
  res = curl_multi_remove_handle(multiHandle, curl);
  if(res)
    fprintf(stderr, "curl_multi_remove_handle() failed, "
            "with code %d\n", (int)res);
  else
    fprintf(stderr, "curl_multi_remove_handle() succeeded\n");

test_cleanup:

  /* undocumented cleanup sequence - type UB */

  curl_easy_cleanup(curl);
  curl_multi_cleanup(multiHandle);
  curl_global_cleanup();

  return (int)res;
}