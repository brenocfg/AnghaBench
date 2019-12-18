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
struct subchannel {int /*<<< orphan*/  lpm; } ;
struct device_attribute {int dummy; } ;
struct device {int /*<<< orphan*/  parent; } ;
struct ccw_device {TYPE_1__* private; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {int state; } ;

/* Variables and functions */
#define  DEV_STATE_BOXED 131 
#define  DEV_STATE_DISCONNECTED 130 
#define  DEV_STATE_DISCONNECTED_SENSE_ID 129 
#define  DEV_STATE_NOT_OPER 128 
 scalar_t__ ccw_device_is_orphan (struct ccw_device*) ; 
 int /*<<< orphan*/  sprintf (char*,char*) ; 
 struct ccw_device* to_ccwdev (struct device*) ; 
 struct subchannel* to_subchannel (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t
available_show (struct device *dev, struct device_attribute *attr, char *buf)
{
	struct ccw_device *cdev = to_ccwdev(dev);
	struct subchannel *sch;

	if (ccw_device_is_orphan(cdev))
		return sprintf(buf, "no device\n");
	switch (cdev->private->state) {
	case DEV_STATE_BOXED:
		return sprintf(buf, "boxed\n");
	case DEV_STATE_DISCONNECTED:
	case DEV_STATE_DISCONNECTED_SENSE_ID:
	case DEV_STATE_NOT_OPER:
		sch = to_subchannel(dev->parent);
		if (!sch->lpm)
			return sprintf(buf, "no path\n");
		else
			return sprintf(buf, "no device\n");
	default:
		/* All other states considered fine. */
		return sprintf(buf, "good\n");
	}
}