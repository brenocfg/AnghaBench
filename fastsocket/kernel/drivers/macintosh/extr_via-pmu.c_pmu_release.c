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
struct pmu_private {scalar_t__ backlight_locker; int /*<<< orphan*/  list; } ;
struct inode {int dummy; } ;
struct file {struct pmu_private* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  all_pvt_lock ; 
 int /*<<< orphan*/  kfree (struct pmu_private*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pmac_backlight_enable () ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int
pmu_release(struct inode *inode, struct file *file)
{
	struct pmu_private *pp = file->private_data;
	unsigned long flags;

	if (pp != 0) {
		file->private_data = NULL;
		spin_lock_irqsave(&all_pvt_lock, flags);
		list_del(&pp->list);
		spin_unlock_irqrestore(&all_pvt_lock, flags);

#if defined(CONFIG_INPUT_ADBHID) && defined(CONFIG_PMAC_BACKLIGHT)
		if (pp->backlight_locker)
			pmac_backlight_enable();
#endif

		kfree(pp);
	}
	return 0;
}