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
struct block_device {TYPE_1__* bd_disk; } ;
struct ace_device {int /*<<< orphan*/  lock; scalar_t__ users; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  fmode_t ;
struct TYPE_2__ {struct ace_device* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  check_disk_change (struct block_device*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int ace_open(struct block_device *bdev, fmode_t mode)
{
	struct ace_device *ace = bdev->bd_disk->private_data;
	unsigned long flags;

	dev_dbg(ace->dev, "ace_open() users=%i\n", ace->users + 1);

	spin_lock_irqsave(&ace->lock, flags);
	ace->users++;
	spin_unlock_irqrestore(&ace->lock, flags);

	check_disk_change(bdev);
	return 0;
}