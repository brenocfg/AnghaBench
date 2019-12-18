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
struct v4l2_device {int /*<<< orphan*/ * dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void v4l2_device_disconnect(struct v4l2_device *v4l2_dev)
{
	if (v4l2_dev->dev) {
		dev_set_drvdata(v4l2_dev->dev, NULL);
		v4l2_dev->dev = NULL;
	}
}