#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int ssize_t ;
struct TYPE_4__ {int tfd; int /*<<< orphan*/  still_running; int /*<<< orphan*/  multi; } ;
typedef  TYPE_1__ GlobalInfo ;
typedef  int /*<<< orphan*/  CURLMcode ;

/* Variables and functions */
 int /*<<< orphan*/  CURL_SOCKET_TIMEOUT ; 
 scalar_t__ EAGAIN ; 
 int /*<<< orphan*/  MSG_OUT ; 
 int /*<<< orphan*/  check_multi_info (TYPE_1__*) ; 
 int /*<<< orphan*/  curl_multi_socket_action (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  mcode_or_die (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int read (int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void timer_cb(GlobalInfo* g, int revents)
{
  CURLMcode rc;
  uint64_t count = 0;
  ssize_t err = 0;

  err = read(g->tfd, &count, sizeof(uint64_t));
  if(err == -1) {
    /* Note that we may call the timer callback even if the timerfd isn't
     * readable. It's possible that there are multiple events stored in the
     * epoll buffer (i.e. the timer may have fired multiple times). The
     * event count is cleared after the first call so future events in the
     * epoll buffer will fail to read from the timer. */
    if(errno == EAGAIN) {
      fprintf(MSG_OUT, "EAGAIN on tfd %d\n", g->tfd);
      return;
    }
  }
  if(err != sizeof(uint64_t)) {
    fprintf(stderr, "read(tfd) == %ld", err);
    perror("read(tfd)");
  }

  rc = curl_multi_socket_action(g->multi,
                                  CURL_SOCKET_TIMEOUT, 0, &g->still_running);
  mcode_or_die("timer_cb: curl_multi_socket_action", rc);
  check_multi_info(g);
}