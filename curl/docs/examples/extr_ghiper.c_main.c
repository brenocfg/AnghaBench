#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  multi; } ;
typedef  TYPE_1__ GlobalInfo ;
typedef  int /*<<< orphan*/  GMainLoop ;
typedef  int /*<<< orphan*/  GIOChannel ;

/* Variables and functions */
 int /*<<< orphan*/  CURLMOPT_SOCKETDATA ; 
 int /*<<< orphan*/  CURLMOPT_SOCKETFUNCTION ; 
 int /*<<< orphan*/  CURLMOPT_TIMERDATA ; 
 int /*<<< orphan*/  CURLMOPT_TIMERFUNCTION ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  G_IO_IN ; 
 int /*<<< orphan*/  curl_multi_cleanup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  curl_multi_init () ; 
 int /*<<< orphan*/  curl_multi_setopt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  fifo_cb ; 
 int /*<<< orphan*/  g_io_add_watch (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/ * g_io_channel_unix_new (int) ; 
 int /*<<< orphan*/ * g_main_loop_new (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_main_loop_run (int /*<<< orphan*/ *) ; 
 TYPE_1__* g_malloc0 (int) ; 
 int init_fifo () ; 
 TYPE_1__* sock_cb ; 
 TYPE_1__* update_timeout_cb ; 

int main(int argc, char **argv)
{
  GlobalInfo *g;
  GMainLoop*gmain;
  int fd;
  GIOChannel* ch;
  g = g_malloc0(sizeof(GlobalInfo));

  fd = init_fifo();
  ch = g_io_channel_unix_new(fd);
  g_io_add_watch(ch, G_IO_IN, fifo_cb, g);
  gmain = g_main_loop_new(NULL, FALSE);
  g->multi = curl_multi_init();
  curl_multi_setopt(g->multi, CURLMOPT_SOCKETFUNCTION, sock_cb);
  curl_multi_setopt(g->multi, CURLMOPT_SOCKETDATA, g);
  curl_multi_setopt(g->multi, CURLMOPT_TIMERFUNCTION, update_timeout_cb);
  curl_multi_setopt(g->multi, CURLMOPT_TIMERDATA, g);

  /* we don't call any curl_multi_socket*() function yet as we have no handles
     added! */

  g_main_loop_run(gmain);
  curl_multi_cleanup(g->multi);
  return 0;
}