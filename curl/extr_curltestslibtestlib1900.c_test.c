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
struct timeval {int tv_sec; long tv_usec; } ;
typedef  int /*<<< orphan*/  fd_set ;
struct TYPE_4__ {int result; } ;
struct TYPE_5__ {scalar_t__ msg; scalar_t__ easy_handle; TYPE_1__ data; } ;
typedef  TYPE_2__ CURLMsg ;
typedef  int /*<<< orphan*/  CURLM ;

/* Variables and functions */
 int /*<<< orphan*/  CURLMOPT_CHUNK_LENGTH_PENALTY_SIZE ; 
 int /*<<< orphan*/  CURLMOPT_CONTENT_LENGTH_PENALTY_SIZE ; 
 int /*<<< orphan*/  CURLMOPT_MAX_HOST_CONNECTIONS ; 
 int /*<<< orphan*/  CURLMOPT_MAX_PIPELINE_LENGTH ; 
 int /*<<< orphan*/  CURLMOPT_PIPELINING ; 
 int /*<<< orphan*/  CURLMOPT_PIPELINING_SERVER_BL ; 
 int /*<<< orphan*/  CURLMOPT_PIPELINING_SITE_BL ; 
 scalar_t__ CURLMSG_DONE ; 
 int /*<<< orphan*/  CURL_GLOBAL_ALL ; 
 int /*<<< orphan*/  FD_ZERO (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  abort_on_test_timeout () ; 
 int /*<<< orphan*/  create_handles () ; 
 int /*<<< orphan*/  curl_global_cleanup () ; 
 int /*<<< orphan*/  curl_global_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  curl_multi_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  curl_multi_fdset (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 TYPE_2__* curl_multi_info_read (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  curl_multi_perform (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  curl_multi_remove_handle (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  curl_multi_timeout (int /*<<< orphan*/ *,long*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  free_urls () ; 
 scalar_t__* handles ; 
 int /*<<< orphan*/  libtest_arg2 ; 
 int /*<<< orphan*/  multi_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  multi_setopt (int /*<<< orphan*/ *,int /*<<< orphan*/ ,long) ; 
 int num_handles ; 
 scalar_t__ parse_url_file (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int,int) ; 
 int /*<<< orphan*/  remove_handles () ; 
 int /*<<< orphan*/  select_test (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timeval*) ; 
 long server_blacklist ; 
 int /*<<< orphan*/  setup_handle (char*,int /*<<< orphan*/ *,int) ; 
 long site_blacklist ; 
 int /*<<< orphan*/  start_test_timing () ; 
 int /*<<< orphan*/  stdout ; 
 scalar_t__ tutil_tvdiff (struct timeval,struct timeval) ; 
 struct timeval tutil_tvnow () ; 
 scalar_t__* urltime ; 

int test(char *URL)
{
  int res = 0;
  CURLM *m = NULL;
  CURLMsg *msg; /* for picking up messages with the transfer status */
  int msgs_left; /* how many messages are left */
  int running = 0;
  int handlenum = 0;
  struct timeval last_handle_add;

  if(parse_url_file(libtest_arg2) <= 0)
    goto test_cleanup;

  start_test_timing();

  curl_global_init(CURL_GLOBAL_ALL);

  multi_init(m);

  create_handles();

  multi_setopt(m, CURLMOPT_PIPELINING, 1L);
  multi_setopt(m, CURLMOPT_MAX_HOST_CONNECTIONS, 2L);
  multi_setopt(m, CURLMOPT_MAX_PIPELINE_LENGTH, 3L);
  multi_setopt(m, CURLMOPT_CONTENT_LENGTH_PENALTY_SIZE, 15000L);
  multi_setopt(m, CURLMOPT_CHUNK_LENGTH_PENALTY_SIZE, 10000L);

  multi_setopt(m, CURLMOPT_PIPELINING_SITE_BL, site_blacklist);
  multi_setopt(m, CURLMOPT_PIPELINING_SERVER_BL, server_blacklist);

  last_handle_add = tutil_tvnow();

  for(;;) {
    struct timeval interval;
    struct timeval now;
    fd_set rd, wr, exc;
    int maxfd = -99;
    long timeout;

    interval.tv_sec = 1;
    interval.tv_usec = 0;

    if(handlenum < num_handles) {
      now = tutil_tvnow();
      if(tutil_tvdiff(now, last_handle_add) >= urltime[handlenum]) {
        fprintf(stdout, "Adding handle %d\n", handlenum);
        setup_handle(URL, m, handlenum);
        last_handle_add = now;
        handlenum++;
      }
    }

    curl_multi_perform(m, &running);

    abort_on_test_timeout();

    /* See how the transfers went */
    do {
      msg = curl_multi_info_read(m, &msgs_left);
      if(msg && msg->msg == CURLMSG_DONE) {
        int i;

        /* Find out which handle this message is about */
        for(i = 0; i < num_handles; i++) {
          int found = (msg->easy_handle == handles[i]);
          if(found)
            break;
        }

        printf("Handle %d Completed with status %d\n", i, msg->data.result);
        curl_multi_remove_handle(m, handles[i]);
      }
    } while(msg);

    if(handlenum == num_handles && !running) {
      break; /* done */
    }

    FD_ZERO(&rd);
    FD_ZERO(&wr);
    FD_ZERO(&exc);

    curl_multi_fdset(m, &rd, &wr, &exc, &maxfd);

    /* At this point, maxfd is guaranteed to be greater or equal than -1. */

    curl_multi_timeout(m, &timeout);

    if(timeout < 0)
      timeout = 1;

    interval.tv_sec = timeout / 1000;
    interval.tv_usec = (timeout % 1000) * 1000;

    interval.tv_sec = 0;
    interval.tv_usec = 1000;

    select_test(maxfd + 1, &rd, &wr, &exc, &interval);

    abort_on_test_timeout();
  }

test_cleanup:

  remove_handles();

  /* undocumented cleanup sequence - type UB */

  curl_multi_cleanup(m);
  curl_global_cleanup();

  free_urls();
  return res;
}