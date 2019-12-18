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
struct se_tmr_req {int /*<<< orphan*/  tmr_list; struct se_device* tmr_dev; } ;
struct se_device {int /*<<< orphan*/  se_tmr_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct se_tmr_req*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void core_tmr_release_req(
	struct se_tmr_req *tmr)
{
	struct se_device *dev = tmr->tmr_dev;
	unsigned long flags;

	if (!dev) {
		kfree(tmr);
		return;
	}

	spin_lock_irqsave(&dev->se_tmr_lock, flags);
	list_del(&tmr->tmr_list);
	spin_unlock_irqrestore(&dev->se_tmr_lock, flags);

	kfree(tmr);
}