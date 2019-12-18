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
struct TYPE_2__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  entry; } ;
struct platform_device {TYPE_1__ archdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  PDEV_ARCHDATA_FLAG_IDLE ; 
 int /*<<< orphan*/  __clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hwblk_lock ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void platform_pm_runtime_not_idle(struct platform_device *pdev)
{
	unsigned long flags;

	/* remove device from idle list */
	spin_lock_irqsave(&hwblk_lock, flags);
	if (test_bit(PDEV_ARCHDATA_FLAG_IDLE, &pdev->archdata.flags)) {
		list_del(&pdev->archdata.entry);
		__clear_bit(PDEV_ARCHDATA_FLAG_IDLE, &pdev->archdata.flags);
	}
	spin_unlock_irqrestore(&hwblk_lock, flags);
}