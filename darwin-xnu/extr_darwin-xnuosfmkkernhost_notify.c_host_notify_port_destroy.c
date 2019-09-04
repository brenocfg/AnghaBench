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
typedef  int /*<<< orphan*/  queue_entry_t ;
typedef  TYPE_1__* ipc_port_t ;
typedef  TYPE_2__* host_notify_t ;
struct TYPE_11__ {TYPE_1__* port; } ;
struct TYPE_10__ {scalar_t__ ip_kobject; } ;

/* Variables and functions */
 scalar_t__ IKOT_HOST_NOTIFY ; 
 int /*<<< orphan*/  IKOT_NONE ; 
 int /*<<< orphan*/  IKO_NULL ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  host_notify_lock ; 
 int /*<<< orphan*/  host_notify_zone ; 
 scalar_t__ ip_kotype (TYPE_1__*) ; 
 int /*<<< orphan*/  ip_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  ip_unlock (TYPE_1__*) ; 
 int /*<<< orphan*/  ipc_kobject_set_atomically (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipc_port_release_sonce (TYPE_1__*) ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  remqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfree (int /*<<< orphan*/ ,TYPE_2__*) ; 

void
host_notify_port_destroy(
	ipc_port_t			port)
{
	host_notify_t		entry;

	lck_mtx_lock(&host_notify_lock);

	ip_lock(port);
	if (ip_kotype(port) == IKOT_HOST_NOTIFY) {
		entry = (host_notify_t)port->ip_kobject;
		assert(entry != NULL);
		ipc_kobject_set_atomically(port, IKO_NULL, IKOT_NONE);
		ip_unlock(port);

		assert(entry->port == port);
		remqueue((queue_entry_t)entry);
		lck_mtx_unlock(&host_notify_lock);
		zfree(host_notify_zone, entry);

		ipc_port_release_sonce(port);
		return;
	}
	ip_unlock(port);

	lck_mtx_unlock(&host_notify_lock);
}