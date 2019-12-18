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
struct device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct ccw_device {struct ccw_device* private; TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct ccw_device*) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ ) ; 
 struct ccw_device* to_ccwdev (struct device*) ; 

__attribute__((used)) static void
ccw_device_release(struct device *dev)
{
	struct ccw_device *cdev;

	cdev = to_ccwdev(dev);
	/* Release reference of parent subchannel. */
	put_device(cdev->dev.parent);
	kfree(cdev->private);
	kfree(cdev);
}