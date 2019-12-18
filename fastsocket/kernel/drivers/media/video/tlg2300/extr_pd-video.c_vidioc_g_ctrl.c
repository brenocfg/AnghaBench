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
typedef  int /*<<< orphan*/  tuner_param ;
struct v4l2_control {int /*<<< orphan*/  value; int /*<<< orphan*/  id; } ;
struct tuner_custom_parameter_s {int /*<<< orphan*/  param_value; } ;
struct poseidon_control {int /*<<< orphan*/  vc_id; } ;
struct poseidon {int /*<<< orphan*/  lock; } ;
struct front_face {struct poseidon* pd; } ;
struct file {int dummy; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  TUNER_CUSTOM_PARAMETER ; 
 struct poseidon_control* check_control_id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ send_get_req (struct poseidon*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct tuner_custom_parameter_s*,scalar_t__*,int) ; 

__attribute__((used)) static int vidioc_g_ctrl(struct file *file, void *fh, struct v4l2_control *ctrl)
{
	struct front_face *front = fh;
	struct poseidon *pd = front->pd;
	struct poseidon_control *control = NULL;
	struct tuner_custom_parameter_s tuner_param;
	s32 ret = 0, cmd_status;

	control = check_control_id(ctrl->id);
	if (!control)
		return -EINVAL;

	mutex_lock(&pd->lock);
	ret = send_get_req(pd, TUNER_CUSTOM_PARAMETER, control->vc_id,
			&tuner_param, &cmd_status, sizeof(tuner_param));
	mutex_unlock(&pd->lock);

	if (ret || cmd_status)
		return -1;

	ctrl->value = tuner_param.param_value;
	return 0;
}