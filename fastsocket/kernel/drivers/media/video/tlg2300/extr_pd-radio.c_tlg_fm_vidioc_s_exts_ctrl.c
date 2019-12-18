#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct v4l2_ext_controls {scalar_t__ ctrl_class; int count; struct v4l2_ext_control* controls; } ;
struct v4l2_ext_control {scalar_t__ id; size_t value; } ;
struct TYPE_2__ {int pre_emphasis; } ;
struct poseidon {TYPE_1__ radio_data; } ;
struct file {struct poseidon* private_data; } ;

/* Variables and functions */
 int EINVAL ; 
 size_t MAX_PREEMPHASIS ; 
 int /*<<< orphan*/  TUNER_AUD_ANA_STD ; 
 scalar_t__ V4L2_CID_TUNE_PREEMPHASIS ; 
 scalar_t__ V4L2_CTRL_CLASS_FM_TX ; 
 int* preemphasis ; 
 int /*<<< orphan*/  send_set_req (struct poseidon*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int tlg_fm_vidioc_s_exts_ctrl(struct file *file, void *fh,
			struct v4l2_ext_controls *ctrls)
{
	int i;

	if (ctrls->ctrl_class != V4L2_CTRL_CLASS_FM_TX)
		return -EINVAL;

	for (i = 0; i < ctrls->count; i++) {
		struct v4l2_ext_control *ctrl = ctrls->controls + i;

		if (ctrl->id != V4L2_CID_TUNE_PREEMPHASIS)
			continue;

		if (ctrl->value >= 0 && ctrl->value < MAX_PREEMPHASIS) {
			struct poseidon *p = file->private_data;
			int pre_emphasis = preemphasis[ctrl->value];
			u32 status;

			send_set_req(p, TUNER_AUD_ANA_STD,
						pre_emphasis, &status);
			p->radio_data.pre_emphasis = pre_emphasis;
		}
	}
	return 0;
}