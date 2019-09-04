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
typedef  scalar_t__ u_int32_t ;
typedef  TYPE_1__* socket_t ;
typedef  int /*<<< orphan*/ * sock_evupcall ;
struct TYPE_4__ {scalar_t__ so_eventmask; int /*<<< orphan*/ * so_eventarg; int /*<<< orphan*/ * so_event; } ;

/* Variables and functions */
 int /*<<< orphan*/  socket_lock_assert_owned (TYPE_1__*) ; 
 int /*<<< orphan*/ * sonullevent ; 

void
sock_catchevents_locked(socket_t sock, sock_evupcall ecallback, void *econtext,
    u_int32_t emask)
{
	socket_lock_assert_owned(sock);

	/*
	 * Note that we don't wait for any in progress upcall to complete.
	 */
	if (ecallback != NULL) {
		sock->so_event = ecallback;
		sock->so_eventarg = econtext;
		sock->so_eventmask = emask;
	} else {
		sock->so_event = sonullevent;
		sock->so_eventarg = NULL;
		sock->so_eventmask = 0;
	}
}