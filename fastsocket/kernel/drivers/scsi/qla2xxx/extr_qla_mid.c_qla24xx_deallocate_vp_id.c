#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
struct qla_hw_data {int /*<<< orphan*/  vport_lock; int /*<<< orphan*/  vp_idx_map; int /*<<< orphan*/  num_vhosts; int /*<<< orphan*/  vport_slock; } ;
struct TYPE_3__ {int /*<<< orphan*/  vp_idx; int /*<<< orphan*/  list; int /*<<< orphan*/  vref_count; struct qla_hw_data* hw; } ;
typedef  TYPE_1__ scsi_qla_host_t ;

/* Variables and functions */
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void
qla24xx_deallocate_vp_id(scsi_qla_host_t *vha)
{
	uint16_t vp_id;
	struct qla_hw_data *ha = vha->hw;
	unsigned long flags = 0;

	mutex_lock(&ha->vport_lock);
	/*
	 * Wait for all pending activities to finish before removing vport from
	 * the list.
	 * Lock needs to be held for safe removal from the list (it
	 * ensures no active vp_list traversal while the vport is removed
	 * from the queue)
	 */
	spin_lock_irqsave(&ha->vport_slock, flags);
	while (atomic_read(&vha->vref_count)) {
		spin_unlock_irqrestore(&ha->vport_slock, flags);

		msleep(500);

		spin_lock_irqsave(&ha->vport_slock, flags);
	}
	list_del(&vha->list);
	spin_unlock_irqrestore(&ha->vport_slock, flags);

	vp_id = vha->vp_idx;
	ha->num_vhosts--;
	clear_bit(vp_id, ha->vp_idx_map);

	mutex_unlock(&ha->vport_lock);
}