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
struct poseidon_control {struct v4l2_queryctrl v4l2_ctrl; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 struct poseidon_control* check_control_id (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vidioc_queryctrl(struct file *file, void *fh,
			struct v4l2_queryctrl *a)
{
	struct poseidon_control *control = NULL;

	control = check_control_id(a->id);
	if (!control)
		return -EINVAL;

	*a = control->v4l2_ctrl;
	return 0;
}