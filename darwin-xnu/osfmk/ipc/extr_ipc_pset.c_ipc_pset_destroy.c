#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* ipc_pset_t ;
struct TYPE_7__ {int /*<<< orphan*/  io_bits; } ;
struct TYPE_8__ {int /*<<< orphan*/  ips_messages; TYPE_1__ ips_object; } ;

/* Variables and functions */
 int /*<<< orphan*/  IO_BITS_ACTIVE ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  imq_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  imq_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ipc_mqueue_changed (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ipc_mqueue_deinit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ipc_mqueue_remove_all (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ips_active (TYPE_2__*) ; 
 int /*<<< orphan*/  ips_release (TYPE_2__*) ; 
 int /*<<< orphan*/  ips_unlock (TYPE_2__*) ; 

void
ipc_pset_destroy(
	ipc_pset_t	pset)
{
	assert(ips_active(pset));

	pset->ips_object.io_bits &= ~IO_BITS_ACTIVE;

	/*
	 * remove all the member message queues
	 * AND remove this message queue from any containing sets
	 */
	ipc_mqueue_remove_all(&pset->ips_messages);

	/*
	 * Set all waiters on the portset running to
	 * discover the change.
	 */
	imq_lock(&pset->ips_messages);
	ipc_mqueue_changed(&pset->ips_messages);
	imq_unlock(&pset->ips_messages);

	ipc_mqueue_deinit(&pset->ips_messages);

	ips_unlock(pset);
	ips_release(pset);       /* consume the ref our caller gave us */
}