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
struct v4l2_queryctrl {int id; scalar_t__ type; } ;
struct em28xx {int /*<<< orphan*/  v4l2_dev; } ;
typedef  int /*<<< orphan*/  qc ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  core ; 
 int /*<<< orphan*/  memset (struct v4l2_queryctrl*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  queryctrl ; 
 int /*<<< orphan*/  v4l2_device_call_all (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct v4l2_queryctrl*) ; 

__attribute__((used)) static int check_subdev_ctrl(struct em28xx *dev, int id)
{
	struct v4l2_queryctrl qc;

	memset(&qc, 0, sizeof(qc));
	qc.id = id;

	/* enumerate V4L2 device controls */
	v4l2_device_call_all(&dev->v4l2_dev, 0, core, queryctrl, &qc);

	if (qc.type)
		return 0;
	else
		return -EINVAL;
}