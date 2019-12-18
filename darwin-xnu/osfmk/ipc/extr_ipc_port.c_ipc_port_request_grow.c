#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct ipc_port_request {int dummy; } ;
typedef  int /*<<< orphan*/  kern_return_t ;
typedef  TYPE_1__* ipc_table_size_t ;
typedef  scalar_t__ ipc_table_elems_t ;
typedef  TYPE_2__* ipc_port_t ;
typedef  TYPE_3__* ipc_port_request_t ;
typedef  scalar_t__ ipc_port_request_index_t ;
struct TYPE_18__ {scalar_t__ ipr_next; TYPE_1__* ipr_size; int /*<<< orphan*/  ipr_name; } ;
struct TYPE_17__ {TYPE_3__* ip_requests; } ;
struct TYPE_16__ {scalar_t__ its_size; } ;

/* Variables and functions */
 TYPE_3__* IPR_NULL ; 
 scalar_t__ ITS_SIZE_NONE ; 
 int /*<<< orphan*/  KERN_NO_SPACE ; 
 int /*<<< orphan*/  KERN_RESOURCE_SHORTAGE ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 int /*<<< orphan*/  MACH_PORT_NULL ; 
 int /*<<< orphan*/  assert (int) ; 
 int ip_active (TYPE_2__*) ; 
 int /*<<< orphan*/  ip_lock (TYPE_2__*) ; 
 int /*<<< orphan*/  ip_reference (TYPE_2__*) ; 
 int /*<<< orphan*/  ip_release (TYPE_2__*) ; 
 int /*<<< orphan*/  ip_unlock (TYPE_2__*) ; 
 TYPE_1__* ipc_table_requests ; 
 TYPE_3__* it_requests_alloc (TYPE_1__*) ; 
 int /*<<< orphan*/  it_requests_free (TYPE_1__*,TYPE_3__*) ; 
 int /*<<< orphan*/  memcpy (void*,void const*,scalar_t__) ; 

kern_return_t
ipc_port_request_grow(
	ipc_port_t		port,
	ipc_table_elems_t 	target_size)
{
	ipc_table_size_t its;
	ipc_port_request_t otable, ntable;

	assert(ip_active(port));

	otable = port->ip_requests;
	if (otable == IPR_NULL)
		its = &ipc_table_requests[0];
	else
		its = otable->ipr_size + 1;

	if (target_size != ITS_SIZE_NONE) {
		if ((otable != IPR_NULL) &&
		    (target_size <= otable->ipr_size->its_size)) {
			ip_unlock(port);
			return KERN_SUCCESS;
	        }
		while ((its->its_size) && (its->its_size < target_size)) {
			its++;
		}
		if (its->its_size == 0) {
			ip_unlock(port);
			return KERN_NO_SPACE;
		}
	}

	ip_reference(port);
	ip_unlock(port);

	if ((its->its_size == 0) ||
	    ((ntable = it_requests_alloc(its)) == IPR_NULL)) {
		ip_release(port);
		return KERN_RESOURCE_SHORTAGE;
	}

	ip_lock(port);

	/*
	 *	Check that port is still active and that nobody else
	 *	has slipped in and grown the table on us.  Note that
	 *	just checking if the current table pointer == otable
	 *	isn't sufficient; must check ipr_size.
	 */

	if (ip_active(port) && (port->ip_requests == otable) &&
	    ((otable == IPR_NULL) || (otable->ipr_size+1 == its))) {
		ipc_table_size_t oits;
		ipc_table_elems_t osize, nsize;
		ipc_port_request_index_t free, i;

		/* copy old table to new table */

		if (otable != IPR_NULL) {
			oits = otable->ipr_size;
			osize = oits->its_size;
			free = otable->ipr_next;

			(void) memcpy((void *)(ntable + 1),
			      (const void *)(otable + 1),
			      (osize - 1) * sizeof(struct ipc_port_request));
		} else {
			osize = 1;
			oits = 0;
			free = 0;
		}

		nsize = its->its_size;
		assert(nsize > osize);

		/* add new elements to the new table's free list */

		for (i = osize; i < nsize; i++) {
			ipc_port_request_t ipr = &ntable[i];

			ipr->ipr_name = MACH_PORT_NULL;
			ipr->ipr_next = free;
			free = i;
		}

		ntable->ipr_next = free;
		ntable->ipr_size = its;
		port->ip_requests = ntable;
		ip_unlock(port);
		ip_release(port);

		if (otable != IPR_NULL) {
			it_requests_free(oits, otable);
	        }
	} else {
		ip_unlock(port);
		ip_release(port);
		it_requests_free(its, ntable);
	}

	return KERN_SUCCESS;
}