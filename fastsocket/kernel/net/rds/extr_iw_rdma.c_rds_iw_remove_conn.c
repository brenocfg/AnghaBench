#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct rds_iw_device {int /*<<< orphan*/  spinlock; } ;
struct rds_iw_connection {int /*<<< orphan*/ * rds_iwdev; int /*<<< orphan*/  i_cm_id; int /*<<< orphan*/  iw_node; } ;
struct rds_connection {struct rds_iw_connection* c_transport_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iw_nodev_conns ; 
 int /*<<< orphan*/  iw_nodev_conns_lock ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rds_iw_remove_cm_id (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

void rds_iw_remove_conn(struct rds_iw_device *rds_iwdev, struct rds_connection *conn)
{
	struct rds_iw_connection *ic = conn->c_transport_data;

	/* place conn on nodev_conns_list */
	spin_lock(&iw_nodev_conns_lock);

	spin_lock_irq(&rds_iwdev->spinlock);
	BUG_ON(list_empty(&ic->iw_node));
	list_del(&ic->iw_node);
	spin_unlock_irq(&rds_iwdev->spinlock);

	list_add_tail(&ic->iw_node, &iw_nodev_conns);

	spin_unlock(&iw_nodev_conns_lock);

	rds_iw_remove_cm_id(ic->rds_iwdev, ic->i_cm_id);
	ic->rds_iwdev = NULL;
}