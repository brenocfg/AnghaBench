#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct rds_iw_connection {int /*<<< orphan*/  iw_node; TYPE_1__* rds_iwdev; } ;
typedef  int /*<<< orphan*/  spinlock_t ;
struct TYPE_2__ {int /*<<< orphan*/  spinlock; } ;

/* Variables and functions */
 int /*<<< orphan*/  iw_nodev_conns_lock ; 
 int /*<<< orphan*/  kfree (struct rds_iw_connection*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rdsdebug (char*,struct rds_iw_connection*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

void rds_iw_conn_free(void *arg)
{
	struct rds_iw_connection *ic = arg;
	spinlock_t	*lock_ptr;

	rdsdebug("ic %p\n", ic);

	/*
	 * Conn is either on a dev's list or on the nodev list.
	 * A race with shutdown() or connect() would cause problems
	 * (since rds_iwdev would change) but that should never happen.
	 */
	lock_ptr = ic->rds_iwdev ? &ic->rds_iwdev->spinlock : &iw_nodev_conns_lock;

	spin_lock_irq(lock_ptr);
	list_del(&ic->iw_node);
	spin_unlock_irq(lock_ptr);

	kfree(ic);
}