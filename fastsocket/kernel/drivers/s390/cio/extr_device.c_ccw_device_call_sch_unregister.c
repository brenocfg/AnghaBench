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
struct subchannel {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct ccw_device {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  css_sch_device_unregister (struct subchannel*) ; 
 int /*<<< orphan*/  get_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 
 struct subchannel* to_subchannel (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ccw_device_call_sch_unregister(struct ccw_device *cdev)
{
	struct subchannel *sch;

	/* Get subchannel reference for local processing. */
	if (!get_device(cdev->dev.parent))
		return;
	sch = to_subchannel(cdev->dev.parent);
	css_sch_device_unregister(sch);
	/* Release subchannel reference for local processing. */
	put_device(&sch->dev);
}