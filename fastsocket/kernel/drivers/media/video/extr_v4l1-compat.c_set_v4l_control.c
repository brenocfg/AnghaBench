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
typedef  int (* v4l2_kioctl ) (struct file*,int /*<<< orphan*/ ,struct v4l2_queryctrl*) ;
struct v4l2_queryctrl {int id; int flags; scalar_t__ type; int value; int maximum; int minimum; } ;
struct v4l2_control {int id; int flags; scalar_t__ type; int value; int maximum; int minimum; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int V4L2_CTRL_FLAG_DISABLED ; 
 int V4L2_CTRL_FLAG_GRABBED ; 
 scalar_t__ V4L2_CTRL_TYPE_BOOLEAN ; 
 int /*<<< orphan*/  VIDIOC_QUERYCTRL ; 
 int /*<<< orphan*/  VIDIOC_S_CTRL ; 
 int /*<<< orphan*/  dprintk (char*,int) ; 

__attribute__((used)) static int
set_v4l_control(struct file             *file,
		int			cid,
		int			value,
		v4l2_kioctl             drv)
{
	struct v4l2_queryctrl	qctrl2;
	struct v4l2_control	ctrl2;
	int			err;

	qctrl2.id = cid;
	err = drv(file, VIDIOC_QUERYCTRL, &qctrl2);
	if (err < 0)
		dprintk("VIDIOC_QUERYCTRL: %d\n", err);
	if (err == 0 &&
	    !(qctrl2.flags & V4L2_CTRL_FLAG_DISABLED) &&
	    !(qctrl2.flags & V4L2_CTRL_FLAG_GRABBED)) {
		if (value < 0)
			value = 0;
		if (value > 65535)
			value = 65535;
		if (value && qctrl2.type == V4L2_CTRL_TYPE_BOOLEAN)
			value = 65535;
		ctrl2.id = qctrl2.id;
		ctrl2.value =
			(value * (qctrl2.maximum - qctrl2.minimum)
			 + 32767)
			/ 65535;
		ctrl2.value += qctrl2.minimum;
		err = drv(file, VIDIOC_S_CTRL, &ctrl2);
		if (err < 0)
			dprintk("VIDIOC_S_CTRL: %d\n", err);
	}
	return 0;
}