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
struct zoran_fh {struct zoran* zr; } ;
struct zoran {int dummy; } ;
struct v4l2_queryctrl {scalar_t__ id; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ V4L2_CID_BRIGHTNESS ; 
 scalar_t__ V4L2_CID_HUE ; 
 int /*<<< orphan*/  core ; 
 int /*<<< orphan*/  decoder_call (struct zoran*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct v4l2_queryctrl*) ; 
 int /*<<< orphan*/  queryctrl ; 

__attribute__((used)) static int zoran_queryctrl(struct file *file, void *__fh,
					struct v4l2_queryctrl *ctrl)
{
	struct zoran_fh *fh = __fh;
	struct zoran *zr = fh->zr;

	/* we only support hue/saturation/contrast/brightness */
	if (ctrl->id < V4L2_CID_BRIGHTNESS ||
	    ctrl->id > V4L2_CID_HUE)
		return -EINVAL;

	decoder_call(zr, core, queryctrl, ctrl);

	return 0;
}