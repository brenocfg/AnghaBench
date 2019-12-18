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
struct v4l2_control {int /*<<< orphan*/  value; int /*<<< orphan*/  id; } ;
struct tuner_custom_parameter_s {int /*<<< orphan*/  param_id; int /*<<< orphan*/  param_value; int /*<<< orphan*/  member_0; } ;
struct poseidon_control {int /*<<< orphan*/  vc_id; } ;
struct poseidon {int /*<<< orphan*/  lock; } ;
struct front_face {struct poseidon* pd; } ;
struct file {int dummy; } ;
typedef  int s32 ;

/* Variables and functions */
 int EINVAL ; 
 int HZ ; 
 int /*<<< orphan*/  TAKE_REQUEST ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  TUNER_CUSTOM_PARAMETER ; 
 struct poseidon_control* check_control_id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule_timeout (int) ; 
 int send_set_req (struct poseidon*,int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vidioc_s_ctrl(struct file *file, void *fh, struct v4l2_control *a)
{
	struct tuner_custom_parameter_s param = {0};
	struct poseidon_control *control = NULL;
	struct front_face *front	= fh;
	struct poseidon *pd		= front->pd;
	s32 ret = 0, cmd_status, params;

	control = check_control_id(a->id);
	if (!control)
		return -EINVAL;

	param.param_value = a->value;
	param.param_id	= control->vc_id;
	params = *(s32 *)&param; /* temp code */

	mutex_lock(&pd->lock);
	ret = send_set_req(pd, TUNER_CUSTOM_PARAMETER, params, &cmd_status);
	ret = send_set_req(pd, TAKE_REQUEST, 0, &cmd_status);
	mutex_unlock(&pd->lock);

	set_current_state(TASK_INTERRUPTIBLE);
	schedule_timeout(HZ/4);
	return ret;
}