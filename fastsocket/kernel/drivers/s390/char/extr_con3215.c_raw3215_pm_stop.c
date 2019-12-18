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
struct raw3215_info {int /*<<< orphan*/  cdev; int /*<<< orphan*/  flags; } ;
struct ccw_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  RAW3215_BUFFER_SIZE ; 
 int /*<<< orphan*/  RAW3215_FROZEN ; 
 struct raw3215_info* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_ccwdev_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  raw3215_make_room (struct raw3215_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static int raw3215_pm_stop(struct ccw_device *cdev)
{
	struct raw3215_info *raw;
	unsigned long flags;

	/* Empty the output buffer, then prevent new I/O. */
	raw = dev_get_drvdata(&cdev->dev);
	spin_lock_irqsave(get_ccwdev_lock(raw->cdev), flags);
	raw3215_make_room(raw, RAW3215_BUFFER_SIZE);
	raw->flags |= RAW3215_FROZEN;
	spin_unlock_irqrestore(get_ccwdev_lock(raw->cdev), flags);
	return 0;
}