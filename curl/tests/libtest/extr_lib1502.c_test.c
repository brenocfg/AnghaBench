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
struct timeval {int tv_sec; scalar_t__ tv_usec; } ;
typedef  char curl_slist ;
typedef  int /*<<< orphan*/  redirect ;
typedef  int /*<<< orphan*/  fd_set ;
typedef  int /*<<< orphan*/  CURLM ;
typedef  int /*<<< orphan*/  CURL ;

/* Variables and functions */
 int CURLE_OUT_OF_MEMORY ; 
 int /*<<< orphan*/  CURLOPT_HEADER ; 
 int /*<<< orphan*/  CURLOPT_RESOLVE ; 
 int /*<<< orphan*/  CURLOPT_URL ; 
 int /*<<< orphan*/  CURL_GLOBAL_ALL ; 
 int /*<<< orphan*/  FD_ZERO (int /*<<< orphan*/ *) ; 
 int TEST_ERR_MAJOR_BAD ; 
 int /*<<< orphan*/  abort_on_test_timeout () ; 
 int /*<<< orphan*/  curl_easy_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * curl_easy_duphandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  curl_global_cleanup () ; 
 int /*<<< orphan*/  curl_multi_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  curl_multi_remove_handle (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* curl_slist_append (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  curl_slist_free_all (char*) ; 
 int /*<<< orphan*/  easy_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  easy_setopt (int /*<<< orphan*/ *,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  libtest_arg2 ; 
 int /*<<< orphan*/  libtest_arg3 ; 
 int /*<<< orphan*/  msnprintf (char*,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  multi_add_handle (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  multi_fdset (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  multi_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  multi_perform (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  res_global_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  select_test (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timeval*) ; 
 int /*<<< orphan*/  start_test_timing () ; 
 int /*<<< orphan*/  stderr ; 

int test(char *URL)
{
  CURL *easy = NULL;
  CURL *dup;
  CURLM *multi = NULL;
  int still_running;
  int res = 0;

  char redirect[160];

  /* DNS cache injection */
  struct curl_slist *dns_cache_list;

  msnprintf(redirect, sizeof(redirect), "google.com:%s:%s", libtest_arg2,
            libtest_arg3);

  start_test_timing();

  dns_cache_list = curl_slist_append(NULL, redirect);
  if(!dns_cache_list) {
    fprintf(stderr, "curl_slist_append() failed\n");
    return TEST_ERR_MAJOR_BAD;
  }

  res_global_init(CURL_GLOBAL_ALL);
  if(res) {
    curl_slist_free_all(dns_cache_list);
    return res;
  }

  easy_init(easy);

  easy_setopt(easy, CURLOPT_URL, URL);
  easy_setopt(easy, CURLOPT_HEADER, 1L);
  easy_setopt(easy, CURLOPT_RESOLVE, dns_cache_list);

  dup = curl_easy_duphandle(easy);
  if(dup) {
    curl_easy_cleanup(easy);
    easy = dup;
  }
  else {
    curl_slist_free_all(dns_cache_list);
    curl_easy_cleanup(easy);
    return CURLE_OUT_OF_MEMORY;
  }

  multi_init(multi);

  multi_add_handle(multi, easy);

  multi_perform(multi, &still_running);

  abort_on_test_timeout();

  while(still_running) {
    struct timeval timeout;
    fd_set fdread;
    fd_set fdwrite;
    fd_set fdexcep;
    int maxfd = -99;

    FD_ZERO(&fdread);
    FD_ZERO(&fdwrite);
    FD_ZERO(&fdexcep);
    timeout.tv_sec = 1;
    timeout.tv_usec = 0;

    multi_fdset(multi, &fdread, &fdwrite, &fdexcep, &maxfd);

    /* At this point, maxfd is guaranteed to be greater or equal than -1. */

    select_test(maxfd + 1, &fdread, &fdwrite, &fdexcep, &timeout);

    abort_on_test_timeout();

    multi_perform(multi, &still_running);

    abort_on_test_timeout();
  }

test_cleanup:

#ifdef LIB1502
  /* undocumented cleanup sequence - type UA */
  curl_multi_cleanup(multi);
  curl_easy_cleanup(easy);
  curl_global_cleanup();
#endif

#ifdef LIB1503
  /* proper cleanup sequence - type PA */
  curl_multi_remove_handle(multi, easy);
  curl_multi_cleanup(multi);
  curl_easy_cleanup(easy);
  curl_global_cleanup();
#endif

#ifdef LIB1504
  /* undocumented cleanup sequence - type UB */
  curl_easy_cleanup(easy);
  curl_multi_cleanup(multi);
  curl_global_cleanup();
#endif

#ifdef LIB1505
  /* proper cleanup sequence - type PB */
  curl_multi_remove_handle(multi, easy);
  curl_easy_cleanup(easy);
  curl_multi_cleanup(multi);
  curl_global_cleanup();
#endif

  curl_slist_free_all(dns_cache_list);

  return res;
}