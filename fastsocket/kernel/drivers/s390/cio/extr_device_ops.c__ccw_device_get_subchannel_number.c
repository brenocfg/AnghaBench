#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ccw_device {TYPE_2__* private; } ;
struct TYPE_3__ {int sch_no; } ;
struct TYPE_4__ {TYPE_1__ schid; } ;

/* Variables and functions */

int
_ccw_device_get_subchannel_number(struct ccw_device *cdev)
{
	return cdev->private->schid.sch_no;
}