#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct timeval {int tv_sec; scalar_t__ tv_usec; } ;
struct curl_slist {int dummy; } ;
typedef  int /*<<< orphan*/  fd_set ;
struct TYPE_4__ {int result; } ;
struct TYPE_5__ {scalar_t__ msg; TYPE_1__ data; int /*<<< orphan*/ * easy_handle; } ;
typedef  TYPE_2__ CURLMsg ;
typedef  int /*<<< orphan*/  CURLM ;
typedef  int /*<<< orphan*/  CURL ;

/* Variables and functions */
 scalar_t__ CURLMSG_DONE ; 
 int /*<<< orphan*/  CURLOPT_DEBUGFUNCTION ; 
 int /*<<< orphan*/  CURLOPT_DNS_CACHE_TIMEOUT ; 
 int /*<<< orphan*/  CURLOPT_RESOLVE ; 
 int /*<<< orphan*/  CURLOPT_URL ; 
 int /*<<< orphan*/  CURLOPT_VERBOSE ; 
 int DNS_TIMEOUT ; 
 int /*<<< orphan*/  FD_ZERO (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  abort_on_test_timeout () ; 
 int /*<<< orphan*/  curl_easy_cleanup (int /*<<< orphan*/ *) ; 
 TYPE_2__* curl_multi_info_read (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  curl_multi_remove_handle (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct curl_slist* curl_slist_append (struct curl_slist*,char*) ; 
 int /*<<< orphan*/  curl_slist_free_all (struct curl_slist*) ; 
 int debug_callback ; 
 int /*<<< orphan*/  easy_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  easy_setopt (int /*<<< orphan*/ *,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  multi_add_handle (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  multi_fdset (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  multi_perform (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  select_test (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timeval*) ; 

__attribute__((used)) static int do_one_request(CURLM *m, char *URL, char *resolve)
{
  CURL *curls;
  struct curl_slist *resolve_list = NULL;
  int still_running;
  int res = 0;
  CURLMsg *msg;
  int msgs_left;

  resolve_list = curl_slist_append(resolve_list, resolve);

  easy_init(curls);

  easy_setopt(curls, CURLOPT_URL, URL);
  easy_setopt(curls, CURLOPT_RESOLVE, resolve_list);
  easy_setopt(curls, CURLOPT_DEBUGFUNCTION, debug_callback);
  easy_setopt(curls, CURLOPT_VERBOSE, 1);
  easy_setopt(curls, CURLOPT_DNS_CACHE_TIMEOUT, DNS_TIMEOUT);

  multi_add_handle(m, curls);
  multi_perform(m, &still_running);

  abort_on_test_timeout();

  while(still_running) {
    struct timeval timeout;
    fd_set fdread, fdwrite, fdexcep;
    int maxfd = -99;

    FD_ZERO(&fdread);
    FD_ZERO(&fdwrite);
    FD_ZERO(&fdexcep);
    timeout.tv_sec = 1;
    timeout.tv_usec = 0;

    multi_fdset(m, &fdread, &fdwrite, &fdexcep, &maxfd);
    select_test(maxfd + 1, &fdread, &fdwrite, &fdexcep, &timeout);

    abort_on_test_timeout();
    multi_perform(m, &still_running);

    abort_on_test_timeout();
  }

  do {
    msg = curl_multi_info_read(m, &msgs_left);
    if(msg && msg->msg == CURLMSG_DONE && msg->easy_handle == curls) {
      res = msg->data.result;
      break;
    }
  } while(msg);

test_cleanup:

  curl_multi_remove_handle(m, curls);
  curl_easy_cleanup(curls);
  curl_slist_free_all(resolve_list);

  return res;
}