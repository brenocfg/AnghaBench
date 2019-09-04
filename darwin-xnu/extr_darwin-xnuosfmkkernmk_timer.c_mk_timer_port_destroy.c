#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* mk_timer_t ;
typedef  TYPE_2__* ipc_port_t ;
struct TYPE_11__ {scalar_t__ ip_kobject; } ;
struct TYPE_10__ {scalar_t__ active; int /*<<< orphan*/  lock; int /*<<< orphan*/  is_dead; int /*<<< orphan*/  is_armed; int /*<<< orphan*/  call_entry; TYPE_2__* port; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  IKOT_NONE ; 
 scalar_t__ IKOT_TIMER ; 
 int /*<<< orphan*/  IKO_NULL ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ ip_kotype (TYPE_2__*) ; 
 int /*<<< orphan*/  ip_lock (TYPE_2__*) ; 
 int /*<<< orphan*/  ip_unlock (TYPE_2__*) ; 
 int /*<<< orphan*/  ipc_kobject_set_atomically (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipc_port_release_send (TYPE_2__*) ; 
 int /*<<< orphan*/  mk_timer_zone ; 
 int /*<<< orphan*/  simple_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  simple_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ thread_call_cancel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfree (int /*<<< orphan*/ ,TYPE_1__*) ; 

void
mk_timer_port_destroy(
	ipc_port_t			port)
{
	mk_timer_t			timer = NULL;

	ip_lock(port);
	if (ip_kotype(port) == IKOT_TIMER) {
		timer = (mk_timer_t)port->ip_kobject;
		assert(timer != NULL);
		ipc_kobject_set_atomically(port, IKO_NULL, IKOT_NONE);
		simple_lock(&timer->lock);
		assert(timer->port == port);
	}
	ip_unlock(port);

	if (timer != NULL) {
		if (thread_call_cancel(&timer->call_entry))
			timer->active--;
		timer->is_armed = FALSE;

		timer->is_dead = TRUE;
		if (timer->active == 0) {
			simple_unlock(&timer->lock);
			zfree(mk_timer_zone, timer);

			ipc_port_release_send(port);
			return;
		}

		simple_unlock(&timer->lock);
	}
}