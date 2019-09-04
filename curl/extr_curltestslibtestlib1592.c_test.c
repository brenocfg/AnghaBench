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
 scalar_t__ CURLE_OK ; 
 scalar_t__ CURLM_OK ; 
 int /*<<< orphan*/  CURLOPT_DNS_SERVERS ; 
 int /*<<< orphan*/  CURLOPT_TIMEOUT_MS ; 
 int /*<<< orphan*/  CURLOPT_URL ; 
 int /*<<< orphan*/  CURLOPT_VERBOSE ; 
 int /*<<< orphan*/  CURL_GLOBAL_ALL ; 
 int TEST_HANG_TIMEOUT ; 
 int /*<<< orphan*/  abort_on_test_timeout () ; 
 int /*<<< orphan*/  curl_easy_cleanup (int /*<<< orphan*/ *) ; 
 scalar_t__ curl_easy_setopt (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  curl_global_cleanup () ; 
 int /*<<< orphan*/  curl_multi_cleanup (int /*<<< orphan*/ *) ; 
 scalar_t__ curl_multi_remove_handle (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  easy_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  easy_setopt (int /*<<< orphan*/ *,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  global_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  multi_add_handle (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  multi_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  multi_perform (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  start_test_timing () ; 
 int /*<<< orphan*/  stderr ; 

int test(char *URL)
{
  int stillRunning;
  CURLM *multiHandle = NULL;
  CURL *curl = NULL;
  CURLMcode res = CURLM_OK;
  int timeout;

  global_init(CURL_GLOBAL_ALL);

  multi_init(multiHandle);

  easy_init(curl);

  easy_setopt(curl, CURLOPT_VERBOSE, 1L);
  easy_setopt(curl, CURLOPT_URL, URL);

  /* Set a DNS server that hopefully will not respond when using c-ares. */
  if(curl_easy_setopt(curl, CURLOPT_DNS_SERVERS, "0.0.0.0") == CURLE_OK)
    /* Since we could set the DNS server, presume we are working with a
       resolver that can be cancelled (i.e. c-ares).  Thus,
       curl_multi_remove_handle() should not block even when the resolver
       request is outstanding.  So, set a request timeout _longer_ than the
       test hang timeout so we will fail if the handle removal call incorrectly
       blocks. */
    timeout = TEST_HANG_TIMEOUT * 2;
  else {
    /* If we can't set the DNS server, presume that we are configured to use a
       resolver that can't be cancelled (i.e. the threaded resolver or the
       non-threaded blocking resolver).  So, we just test that the
       curl_multi_remove_handle() call does finish well within our test
       timeout.

       But, it is very unlikely that the resolver request will take any time at
       all because we haven't been able to configure the resolver to use an
       non-responsive DNS server.  At least we exercise the flow.
       */
    fprintf(stderr,
            "CURLOPT_DNS_SERVERS not supported; "
            "assuming curl_multi_remove_handle() will block\n");
    timeout = TEST_HANG_TIMEOUT / 2;
  }

  /* Setting a timeout on the request should ensure that even if we have to
     wait for the resolver during curl_multi_remove_handle(), it won't take
     longer than this, because the resolver request inherits its timeout from
     this. */
  easy_setopt(curl, CURLOPT_TIMEOUT_MS, timeout);

  multi_add_handle(multiHandle, curl);

  /* This should move the handle from INIT => CONNECT => WAITRESOLVE. */
  fprintf(stderr, "curl_multi_perform()...\n");
  multi_perform(multiHandle, &stillRunning);
  fprintf(stderr, "curl_multi_perform() succeeded\n");

  /* Start measuring how long it takes to remove the handle. */
  fprintf(stderr, "curl_multi_remove_handle()...\n");
  start_test_timing();
  res = curl_multi_remove_handle(multiHandle, curl);
  if(res) {
    fprintf(stderr, "curl_multi_remove_handle() failed, "
            "with code %d\n", (int)res);
    goto test_cleanup;
  }
  fprintf(stderr, "curl_multi_remove_handle() succeeded\n");

  /* Fail the test if it took too long to remove.  This happens after the fact,
     and says "it seems that it would have run forever", which isn't true, but
     it's close enough, and simple to do. */
  abort_on_test_timeout();

test_cleanup:
  curl_easy_cleanup(curl);
  curl_multi_cleanup(multiHandle);
  curl_global_cleanup();

  return (int)res;
}