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
struct TYPE_3__ {int numerator; int /*<<< orphan*/  denominator; } ;
struct v4l2_frmivalenum {scalar_t__ index; TYPE_1__ discrete; int /*<<< orphan*/  type; } ;
struct go7007_file {struct go7007* go; } ;
struct go7007 {TYPE_2__* board_info; } ;
struct file {int dummy; } ;
struct TYPE_4__ {int flags; int sensor_flags; int /*<<< orphan*/  sensor_framerate; } ;

/* Variables and functions */
 int EINVAL ; 
 int GO7007_BOARD_HAS_TUNER ; 
 int GO7007_SENSOR_TV ; 
 int /*<<< orphan*/  V4L2_FRMIVAL_TYPE_DISCRETE ; 

__attribute__((used)) static int vidioc_enum_frameintervals(struct file *filp, void *priv,
				      struct v4l2_frmivalenum *fival)
{
	struct go7007 *go = ((struct go7007_file *) priv)->go;

	/* Return -EINVAL, if it is a TV board */
	if ((go->board_info->flags & GO7007_BOARD_HAS_TUNER) ||
	    (go->board_info->sensor_flags & GO7007_SENSOR_TV))
		return -EINVAL;

	if (fival->index > 0)
		return -EINVAL;

	fival->type = V4L2_FRMIVAL_TYPE_DISCRETE;
	fival->discrete.numerator = 1001;
	fival->discrete.denominator = go->board_info->sensor_framerate;

	return 0;
}