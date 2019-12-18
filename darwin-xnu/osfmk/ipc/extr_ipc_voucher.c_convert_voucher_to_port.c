#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_2__ ;
typedef  struct TYPE_24__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* ipc_voucher_t ;
typedef  TYPE_2__* ipc_port_t ;
typedef  scalar_t__ ipc_kobject_t ;
struct TYPE_25__ {scalar_t__ ip_kobject; int ip_srights; int /*<<< orphan*/  ip_mscount; struct TYPE_25__* ip_nsrequest; } ;
struct TYPE_24__ {TYPE_2__* iv_port; int /*<<< orphan*/  iv_refs; } ;

/* Variables and functions */
 scalar_t__ IKOT_VOUCHER ; 
 TYPE_2__* IP_NULL ; 
 int IP_VALID (TYPE_2__*) ; 
 TYPE_1__* IV_NULL ; 
 int /*<<< orphan*/  OSCompareAndSwapPtr (TYPE_2__*,TYPE_2__*,TYPE_2__**) ; 
 int /*<<< orphan*/  assert (int) ; 
 int ip_active (TYPE_2__*) ; 
 scalar_t__ ip_kotype (TYPE_2__*) ; 
 int /*<<< orphan*/  ip_lock (TYPE_2__*) ; 
 int /*<<< orphan*/  ip_unlock (TYPE_2__*) ; 
 int /*<<< orphan*/  ipc_kobject_set_atomically (TYPE_2__*,scalar_t__,scalar_t__) ; 
 TYPE_2__* ipc_port_alloc_kernel () ; 
 int /*<<< orphan*/  ipc_port_dealloc_kernel (TYPE_2__*) ; 
 TYPE_2__* ipc_port_make_send_locked (TYPE_2__*) ; 
 int /*<<< orphan*/  ipc_port_make_sonce_locked (TYPE_2__*) ; 
 int /*<<< orphan*/  ipc_port_nsrequest (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__**) ; 
 int /*<<< orphan*/  ipc_voucher_release (TYPE_1__*) ; 
 scalar_t__ os_ref_get_count (int /*<<< orphan*/ *) ; 

ipc_port_t
convert_voucher_to_port(ipc_voucher_t voucher)
{
	ipc_port_t	port, send;

	if (IV_NULL == voucher)
		return (IP_NULL);

	assert(os_ref_get_count(&voucher->iv_refs) > 0);

	/* create a port if needed */
	port = voucher->iv_port;
	if (!IP_VALID(port)) {
		port = ipc_port_alloc_kernel();
		assert(IP_VALID(port));
		ipc_kobject_set_atomically(port, (ipc_kobject_t) voucher, IKOT_VOUCHER);

		/* If we lose the race, deallocate and pick up the other guy's port */
		if (!OSCompareAndSwapPtr(IP_NULL, port, &voucher->iv_port)) {
			ipc_port_dealloc_kernel(port);
			port = voucher->iv_port;
			assert(ip_kotype(port) == IKOT_VOUCHER);
			assert(port->ip_kobject == (ipc_kobject_t)voucher);
		}
	}
	
	ip_lock(port);
	assert(ip_active(port));
	send = ipc_port_make_send_locked(port);

	if (1 == port->ip_srights) {
		ipc_port_t old_notify;

		/* transfer our ref to the port, and arm the no-senders notification */
		assert(IP_NULL == port->ip_nsrequest);
		ipc_port_nsrequest(port, port->ip_mscount, ipc_port_make_sonce_locked(port), &old_notify);
		/* port unlocked */
		assert(IP_NULL == old_notify);
	} else {
		/* piggyback on the existing port reference, so consume ours */
		ip_unlock(port);
		ipc_voucher_release(voucher);
	}
	return (send);
}