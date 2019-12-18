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
struct inode {int dummy; } ;
struct hpets {int hp_ntimer; struct hpet_dev* hp_dev; struct hpets* hp_next; } ;
struct hpet_dev {int hd_flags; scalar_t__ hd_irqdata; } ;
struct file {int f_mode; struct hpet_dev* private_data; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int FMODE_WRITE ; 
 int HPET_OPEN ; 
 int /*<<< orphan*/  hpet_lock ; 
 int /*<<< orphan*/  hpet_timer_set_irq (struct hpet_dev*) ; 
 struct hpets* hpets ; 
 int /*<<< orphan*/  lock_kernel () ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unlock_kernel () ; 

__attribute__((used)) static int hpet_open(struct inode *inode, struct file *file)
{
	struct hpet_dev *devp;
	struct hpets *hpetp;
	int i;

	if (file->f_mode & FMODE_WRITE)
		return -EINVAL;

	lock_kernel();
	spin_lock_irq(&hpet_lock);

	for (devp = NULL, hpetp = hpets; hpetp && !devp; hpetp = hpetp->hp_next)
		for (i = 0; i < hpetp->hp_ntimer; i++)
			if (hpetp->hp_dev[i].hd_flags & HPET_OPEN)
				continue;
			else {
				devp = &hpetp->hp_dev[i];
				break;
			}

	if (!devp) {
		spin_unlock_irq(&hpet_lock);
		unlock_kernel();
		return -EBUSY;
	}

	file->private_data = devp;
	devp->hd_irqdata = 0;
	devp->hd_flags |= HPET_OPEN;
	spin_unlock_irq(&hpet_lock);
	unlock_kernel();

	hpet_timer_set_irq(devp);

	return 0;
}