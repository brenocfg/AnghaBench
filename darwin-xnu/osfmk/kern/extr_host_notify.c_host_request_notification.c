#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  queue_entry_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
typedef  TYPE_1__* ipc_port_t ;
typedef  int /*<<< orphan*/  ipc_kobject_t ;
typedef  scalar_t__ host_t ;
typedef  TYPE_2__* host_notify_t ;
typedef  size_t host_flavor_t ;
struct TYPE_12__ {TYPE_1__* port; } ;
struct TYPE_11__ {scalar_t__ ip_tempowner; } ;

/* Variables and functions */
 size_t HOST_NOTIFY_TYPE_MAX ; 
 scalar_t__ HOST_NULL ; 
 int /*<<< orphan*/  IKOT_HOST_NOTIFY ; 
 scalar_t__ IKOT_NONE ; 
 int /*<<< orphan*/  IP_VALID (TYPE_1__*) ; 
 int /*<<< orphan*/  KERN_FAILURE ; 
 int /*<<< orphan*/  KERN_INVALID_ARGUMENT ; 
 int /*<<< orphan*/  KERN_INVALID_CAPABILITY ; 
 int /*<<< orphan*/  KERN_RESOURCE_SHORTAGE ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 int /*<<< orphan*/  enqueue_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  host_notify_lock ; 
 int /*<<< orphan*/ * host_notify_queue ; 
 int /*<<< orphan*/  host_notify_zone ; 
 int /*<<< orphan*/  ip_active (TYPE_1__*) ; 
 scalar_t__ ip_kotype (TYPE_1__*) ; 
 int /*<<< orphan*/  ip_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  ip_unlock (TYPE_1__*) ; 
 int /*<<< orphan*/  ipc_kobject_set_atomically (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ zalloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfree (int /*<<< orphan*/ ,TYPE_2__*) ; 

kern_return_t
host_request_notification(
	host_t					host,
	host_flavor_t			notify_type,
	ipc_port_t				port)
{
	host_notify_t		entry;

	if (host == HOST_NULL)
		return (KERN_INVALID_ARGUMENT);

	if (!IP_VALID(port))
		return (KERN_INVALID_CAPABILITY);

	if (notify_type > HOST_NOTIFY_TYPE_MAX || notify_type < 0)
		return (KERN_INVALID_ARGUMENT);

	entry = (host_notify_t)zalloc(host_notify_zone);
	if (entry == NULL)
		return (KERN_RESOURCE_SHORTAGE);

	lck_mtx_lock(&host_notify_lock);

	ip_lock(port);
	if (!ip_active(port) || port->ip_tempowner || ip_kotype(port) != IKOT_NONE) {
		ip_unlock(port);

		lck_mtx_unlock(&host_notify_lock);
		zfree(host_notify_zone, entry);

		return (KERN_FAILURE);
	}

	entry->port = port;
	ipc_kobject_set_atomically(port, (ipc_kobject_t)entry, IKOT_HOST_NOTIFY);
	ip_unlock(port);

	enqueue_tail(&host_notify_queue[notify_type], (queue_entry_t)entry);
	lck_mtx_unlock(&host_notify_lock);

	return (KERN_SUCCESS);
}