#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_7__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {TYPE_2__* data; } ;
struct TYPE_9__ {TYPE_2__* data; } ;
struct TYPE_10__ {int /*<<< orphan*/  multi; int /*<<< orphan*/  loop; TYPE_1__ fifo_event; TYPE_7__ timer_event; } ;
typedef  TYPE_2__ GlobalInfo ;

/* Variables and functions */
 int /*<<< orphan*/  CURLMOPT_SOCKETDATA ; 
 int /*<<< orphan*/  CURLMOPT_SOCKETFUNCTION ; 
 int /*<<< orphan*/  CURLMOPT_TIMERDATA ; 
 int /*<<< orphan*/  CURLMOPT_TIMERFUNCTION ; 
 int /*<<< orphan*/  curl_multi_cleanup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  curl_multi_init () ; 
 int /*<<< orphan*/  curl_multi_setopt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  ev_default_loop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ev_loop (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ev_timer_init (TYPE_7__*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  init_fifo (TYPE_2__*) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 TYPE_2__* multi_timer_cb ; 
 TYPE_2__* sock_cb ; 
 int /*<<< orphan*/  timer_cb ; 

int main(int argc, char **argv)
{
  GlobalInfo g;
  (void)argc;
  (void)argv;

  memset(&g, 0, sizeof(GlobalInfo));
  g.loop = ev_default_loop(0);

  init_fifo(&g);
  g.multi = curl_multi_init();

  ev_timer_init(&g.timer_event, timer_cb, 0., 0.);
  g.timer_event.data = &g;
  g.fifo_event.data = &g;
  curl_multi_setopt(g.multi, CURLMOPT_SOCKETFUNCTION, sock_cb);
  curl_multi_setopt(g.multi, CURLMOPT_SOCKETDATA, &g);
  curl_multi_setopt(g.multi, CURLMOPT_TIMERFUNCTION, multi_timer_cb);
  curl_multi_setopt(g.multi, CURLMOPT_TIMERDATA, &g);

  /* we don't call any curl_multi_socket*() function yet as we have no handles
     added! */

  ev_loop(g.loop, 0);
  curl_multi_cleanup(g.multi);
  return 0;
}