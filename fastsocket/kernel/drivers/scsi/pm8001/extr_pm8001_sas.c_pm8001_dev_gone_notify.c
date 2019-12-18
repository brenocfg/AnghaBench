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
typedef  int /*<<< orphan*/  u32 ;
struct pm8001_hba_info {int /*<<< orphan*/  lock; } ;
struct pm8001_device {scalar_t__ running_req; int /*<<< orphan*/  dev_type; int /*<<< orphan*/  device_id; } ;
struct domain_device {struct pm8001_device* lldd_dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* dereg_dev_req ) (struct pm8001_hba_info*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 TYPE_1__* PM8001_CHIP_DISP ; 
 int /*<<< orphan*/  PM8001_DISC_DBG (struct pm8001_hba_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm8001_exec_internal_task_abort (struct pm8001_hba_info*,struct pm8001_device*,struct domain_device*,int,int /*<<< orphan*/ ) ; 
 struct pm8001_hba_info* pm8001_find_ha_by_dev (struct domain_device*) ; 
 int /*<<< orphan*/  pm8001_free_dev (struct pm8001_device*) ; 
 int /*<<< orphan*/  pm8001_printk (char*,...) ; 
 int /*<<< orphan*/  pm8001_tag_alloc (struct pm8001_hba_info*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct pm8001_hba_info*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pm8001_dev_gone_notify(struct domain_device *dev)
{
	unsigned long flags = 0;
	u32 tag;
	struct pm8001_hba_info *pm8001_ha;
	struct pm8001_device *pm8001_dev = dev->lldd_dev;

	pm8001_ha = pm8001_find_ha_by_dev(dev);
	spin_lock_irqsave(&pm8001_ha->lock, flags);
	pm8001_tag_alloc(pm8001_ha, &tag);
	if (pm8001_dev) {
		u32 device_id = pm8001_dev->device_id;

		PM8001_DISC_DBG(pm8001_ha,
			pm8001_printk("found dev[%d:%x] is gone.\n",
			pm8001_dev->device_id, pm8001_dev->dev_type));
		if (pm8001_dev->running_req) {
			spin_unlock_irqrestore(&pm8001_ha->lock, flags);
			pm8001_exec_internal_task_abort(pm8001_ha, pm8001_dev ,
				dev, 1, 0);
			spin_lock_irqsave(&pm8001_ha->lock, flags);
		}
		PM8001_CHIP_DISP->dereg_dev_req(pm8001_ha, device_id);
		pm8001_free_dev(pm8001_dev);
	} else {
		PM8001_DISC_DBG(pm8001_ha,
			pm8001_printk("Found dev has gone.\n"));
	}
	dev->lldd_dev = NULL;
	spin_unlock_irqrestore(&pm8001_ha->lock, flags);
}