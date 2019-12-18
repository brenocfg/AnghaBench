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
struct v4l2_queryctrl {scalar_t__ id; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ V4L2_CID_BASE ; 
 scalar_t__ V4L2_CID_LASTP1 ; 
 scalar_t__ V4L2_CID_PRIVATE_BASE ; 
 scalar_t__ V4L2_CID_PRIVATE_LASTP1 ; 
 struct v4l2_queryctrl* ctrl_by_id (scalar_t__) ; 
 struct v4l2_queryctrl const no_ctrl ; 

int saa7134_queryctrl(struct file *file, void *priv, struct v4l2_queryctrl *c)
{
	const struct v4l2_queryctrl *ctrl;

	if ((c->id <  V4L2_CID_BASE ||
	     c->id >= V4L2_CID_LASTP1) &&
	    (c->id <  V4L2_CID_PRIVATE_BASE ||
	     c->id >= V4L2_CID_PRIVATE_LASTP1))
		return -EINVAL;
	ctrl = ctrl_by_id(c->id);
	*c = (NULL != ctrl) ? *ctrl : no_ctrl;
	return 0;
}