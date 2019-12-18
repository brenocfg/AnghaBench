#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  curl_socket_t ;
struct TYPE_7__ {int /*<<< orphan*/  evbase; } ;
struct TYPE_6__ {int action; int /*<<< orphan*/  ev; int /*<<< orphan*/  sockfd; int /*<<< orphan*/ * easy; } ;
typedef  TYPE_1__ SockInfo ;
typedef  TYPE_2__ GlobalInfo ;
typedef  int /*<<< orphan*/  CURL ;

/* Variables and functions */
 int CURL_POLL_IN ; 
 int CURL_POLL_OUT ; 
 int EV_PERSIST ; 
 int EV_READ ; 
 int EV_WRITE ; 
 int /*<<< orphan*/  event_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  event_assign (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  event_cb ; 
 int /*<<< orphan*/  event_del (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void setsock(SockInfo *f, curl_socket_t s, CURL *e, int act,
                    GlobalInfo *g)
{
  int kind =
     ((act & CURL_POLL_IN) ? EV_READ : 0) |
     ((act & CURL_POLL_OUT) ? EV_WRITE : 0) | EV_PERSIST;

  f->sockfd = s;
  f->action = act;
  f->easy = e;
  event_del(&f->ev);
  event_assign(&f->ev, g->evbase, f->sockfd, kind, event_cb, g);
  event_add(&f->ev, NULL);
}