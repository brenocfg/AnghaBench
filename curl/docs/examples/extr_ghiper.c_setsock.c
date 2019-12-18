#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  curl_socket_t ;
struct TYPE_3__ {int action; int /*<<< orphan*/  ch; scalar_t__ ev; int /*<<< orphan*/ * easy; int /*<<< orphan*/  sockfd; } ;
typedef  TYPE_1__ SockInfo ;
typedef  int /*<<< orphan*/  GlobalInfo ;
typedef  int GIOCondition ;
typedef  int /*<<< orphan*/  CURL ;

/* Variables and functions */
 int CURL_POLL_IN ; 
 int CURL_POLL_OUT ; 
 int G_IO_IN ; 
 int G_IO_OUT ; 
 int /*<<< orphan*/  event_cb ; 
 scalar_t__ g_io_add_watch (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_source_remove (scalar_t__) ; 

__attribute__((used)) static void setsock(SockInfo *f, curl_socket_t s, CURL *e, int act,
                    GlobalInfo *g)
{
  GIOCondition kind =
    ((act & CURL_POLL_IN) ? G_IO_IN : 0) |
    ((act & CURL_POLL_OUT) ? G_IO_OUT : 0);

  f->sockfd = s;
  f->action = act;
  f->easy = e;
  if(f->ev) {
    g_source_remove(f->ev);
  }
  f->ev = g_io_add_watch(f->ch, kind, event_cb, g);
}