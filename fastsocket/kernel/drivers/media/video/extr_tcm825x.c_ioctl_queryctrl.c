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
struct v4l2_queryctrl {int /*<<< orphan*/  id; } ;
struct vcontrol {struct v4l2_queryctrl qc; } ;
struct v4l2_int_device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 struct vcontrol* find_vctrl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ioctl_queryctrl(struct v4l2_int_device *s,
				struct v4l2_queryctrl *qc)
{
	struct vcontrol *control;

	control = find_vctrl(qc->id);

	if (control == NULL)
		return -EINVAL;

	*qc = control->qc;

	return 0;
}