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
struct sysfs_open_dirent {int /*<<< orphan*/  poll; int /*<<< orphan*/  event; } ;
struct TYPE_2__ {struct sysfs_open_dirent* open; } ;
struct sysfs_dirent {TYPE_1__ s_attr; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  sysfs_open_dirent_lock ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

void sysfs_notify_dirent(struct sysfs_dirent *sd)
{
	struct sysfs_open_dirent *od;
	unsigned long flags;

	spin_lock_irqsave(&sysfs_open_dirent_lock, flags);

	od = sd->s_attr.open;
	if (od) {
		atomic_inc(&od->event);
		wake_up_interruptible(&od->poll);
	}

	spin_unlock_irqrestore(&sysfs_open_dirent_lock, flags);
}