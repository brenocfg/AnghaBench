#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  multi; int /*<<< orphan*/  evbase; int /*<<< orphan*/  timer_event; } ;
typedef  TYPE_1__ GlobalInfo ;

/* Variables and functions */
 int /*<<< orphan*/  CURLMOPT_SOCKETDATA ; 
 int /*<<< orphan*/  CURLMOPT_SOCKETFUNCTION ; 
 int /*<<< orphan*/  CURLMOPT_TIMERDATA ; 
 int /*<<< orphan*/  CURLMOPT_TIMERFUNCTION ; 
 int /*<<< orphan*/  clean_fifo (TYPE_1__*) ; 
 int /*<<< orphan*/  curl_multi_cleanup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  curl_multi_init () ; 
 int /*<<< orphan*/  curl_multi_setopt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  event_base_dispatch (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  event_base_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  event_base_new () ; 
 int /*<<< orphan*/  event_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  evtimer_assign (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  init_fifo (TYPE_1__*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* multi_timer_cb ; 
 TYPE_1__* sock_cb ; 
 int /*<<< orphan*/  timer_cb ; 

int main(int argc, char **argv)
{
  GlobalInfo g;
  (void)argc;
  (void)argv;

  memset(&g, 0, sizeof(GlobalInfo));
  g.evbase = event_base_new();
  init_fifo(&g);
  g.multi = curl_multi_init();
  evtimer_assign(&g.timer_event, g.evbase, timer_cb, &g);

  /* setup the generic multi interface options we want */
  curl_multi_setopt(g.multi, CURLMOPT_SOCKETFUNCTION, sock_cb);
  curl_multi_setopt(g.multi, CURLMOPT_SOCKETDATA, &g);
  curl_multi_setopt(g.multi, CURLMOPT_TIMERFUNCTION, multi_timer_cb);
  curl_multi_setopt(g.multi, CURLMOPT_TIMERDATA, &g);

  /* we don't call any curl_multi_socket*() function yet as we have no handles
     added! */

  event_base_dispatch(g.evbase);

  /* this, of course, won't get called since only way to stop this program is
     via ctrl-C, but it is here to show how cleanup /would/ be done. */
  clean_fifo(&g);
  event_del(&g.timer_event);
  event_base_free(g.evbase);
  curl_multi_cleanup(g.multi);
  return 0;
}