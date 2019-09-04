#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_3__* mig_object_t ;
typedef  scalar_t__ mach_port_mscount_t ;
typedef  TYPE_4__* ipc_port_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_13__ {scalar_t__ imq_seqno; } ;
struct TYPE_16__ {scalar_t__ ip_mscount; TYPE_1__ ip_messages; scalar_t__ ip_kobject; int /*<<< orphan*/  ip_sorights; } ;
struct TYPE_15__ {TYPE_2__* pVtbl; TYPE_4__* port; } ;
struct TYPE_14__ {int /*<<< orphan*/  (* Release ) (int /*<<< orphan*/ *) ;} ;
typedef  int /*<<< orphan*/  IMIGObject ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 TYPE_4__* IP_NULL ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  ip_lock (TYPE_4__*) ; 
 int /*<<< orphan*/  ip_reference (TYPE_4__*) ; 
 int /*<<< orphan*/  ipc_port_destroy (TYPE_4__*) ; 
 int /*<<< orphan*/  ipc_port_nsrequest (TYPE_4__*,scalar_t__,TYPE_4__*,TYPE_4__**) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 

boolean_t
mig_object_no_senders(
	ipc_port_t		port,
	mach_port_mscount_t	mscount)
{
	mig_object_t		mig_object;

	ip_lock(port);
	if (port->ip_mscount > mscount) {
		ipc_port_t 	previous;

		/*
		 * Somebody created new send rights while the
		 * notification was in-flight.  Just create a
		 * new send-once right and re-register with 
		 * the new (higher) mscount threshold.
		 */
		/* make a sonce right for the notification */
		port->ip_sorights++;
		ip_reference(port);
		ipc_port_nsrequest(port, mscount, port, &previous);
		/* port unlocked */

		assert(previous == IP_NULL);
		return (FALSE);
	}

	/*
	 * Clear the port pointer while we have it locked.
	 */
	mig_object = (mig_object_t)port->ip_kobject;
	mig_object->port = IP_NULL;

	/*
	 * Bring the sequence number and mscount in
	 * line with ipc_port_destroy assertion.
	 */
	port->ip_mscount = 0;
	port->ip_messages.imq_seqno = 0;
	ipc_port_destroy(port); /* releases lock */
	
	/*
	 * Release the port's reference on the object.
	 */
	mig_object->pVtbl->Release((IMIGObject *)mig_object);
	return (TRUE);
}