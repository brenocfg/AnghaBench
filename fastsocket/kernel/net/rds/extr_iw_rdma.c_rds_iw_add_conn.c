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
struct rds_iw_device {int /*<<< orphan*/  spinlock; int /*<<< orphan*/  conn_list; } ;
struct rds_iw_connection {struct rds_iw_device* rds_iwdev; int /*<<< orphan*/  iw_node; } ;
struct rds_connection {struct rds_iw_connection* c_transport_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iw_nodev_conns ; 
 int /*<<< orphan*/  iw_nodev_conns_lock ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

void rds_iw_add_conn(struct rds_iw_device *rds_iwdev, struct rds_connection *conn)
{
	struct rds_iw_connection *ic = conn->c_transport_data;

	/* conn was previously on the nodev_conns_list */
	spin_lock_irq(&iw_nodev_conns_lock);
	BUG_ON(list_empty(&iw_nodev_conns));
	BUG_ON(list_empty(&ic->iw_node));
	list_del(&ic->iw_node);

	spin_lock(&rds_iwdev->spinlock);
	list_add_tail(&ic->iw_node, &rds_iwdev->conn_list);
	spin_unlock(&rds_iwdev->spinlock);
	spin_unlock_irq(&iw_nodev_conns_lock);

	ic->rds_iwdev = rds_iwdev;
}