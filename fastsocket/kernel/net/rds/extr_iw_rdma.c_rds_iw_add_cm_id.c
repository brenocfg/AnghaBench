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
struct rds_iw_device {int /*<<< orphan*/  spinlock; int /*<<< orphan*/  cm_id_list; } ;
struct rds_iw_cm_id {int /*<<< orphan*/  list; struct rdma_cm_id* cm_id; } ;
struct rdma_cm_id {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct rds_iw_cm_id* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rds_iw_add_cm_id(struct rds_iw_device *rds_iwdev, struct rdma_cm_id *cm_id)
{
	struct rds_iw_cm_id *i_cm_id;

	i_cm_id = kmalloc(sizeof *i_cm_id, GFP_KERNEL);
	if (!i_cm_id)
		return -ENOMEM;

	i_cm_id->cm_id = cm_id;

	spin_lock_irq(&rds_iwdev->spinlock);
	list_add_tail(&i_cm_id->list, &rds_iwdev->cm_id_list);
	spin_unlock_irq(&rds_iwdev->spinlock);

	return 0;
}