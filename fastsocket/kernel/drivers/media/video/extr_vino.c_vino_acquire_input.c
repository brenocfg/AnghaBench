#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int v4l2_std_id ;
struct vino_channel_settings {scalar_t__ channel; int input; int data_norm; } ;
struct TYPE_10__ {int std; } ;
struct TYPE_7__ {int input; int data_norm; } ;
struct TYPE_6__ {int input; int data_norm; } ;
struct TYPE_9__ {scalar_t__ camera_owner; scalar_t__ decoder_owner; int /*<<< orphan*/  input_lock; TYPE_2__ a; TYPE_1__ b; scalar_t__ decoder; scalar_t__ camera; } ;
struct TYPE_8__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 scalar_t__ VINO_CHANNEL_A ; 
 int VINO_DATA_NORM_D1 ; 
 int VINO_DATA_NORM_PAL ; 
 int VINO_INPUT_COMPOSITE ; 
 int VINO_INPUT_D1 ; 
 int VINO_INPUT_NONE ; 
 scalar_t__ VINO_NO_CHANNEL ; 
 int /*<<< orphan*/  core ; 
 int decoder_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  dprintk (char*,...) ; 
 int /*<<< orphan*/  querystd ; 
 int /*<<< orphan*/  s_routing ; 
 int /*<<< orphan*/  s_std ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  video ; 
 TYPE_5__* vino_data_norms ; 
 TYPE_4__* vino_drvdata ; 
 int /*<<< orphan*/  vino_get_saa7191_input (int) ; 
 TYPE_3__* vino_inputs ; 
 int /*<<< orphan*/  vino_set_default_clipping (struct vino_channel_settings*) ; 
 int /*<<< orphan*/  vino_set_default_framerate (struct vino_channel_settings*) ; 
 int /*<<< orphan*/  vino_set_default_scaling (struct vino_channel_settings*) ; 

__attribute__((used)) static int vino_acquire_input(struct vino_channel_settings *vcs)
{
	unsigned long flags;
	int ret = 0;

	dprintk("vino_acquire_input():\n");

	spin_lock_irqsave(&vino_drvdata->input_lock, flags);

	/* First try D1 and then SAA7191 */
	if (vino_drvdata->camera
	    && (vino_drvdata->camera_owner == VINO_NO_CHANNEL)) {
		vino_drvdata->camera_owner = vcs->channel;
		vcs->input = VINO_INPUT_D1;
		vcs->data_norm = VINO_DATA_NORM_D1;
	} else if (vino_drvdata->decoder
		   && (vino_drvdata->decoder_owner == VINO_NO_CHANNEL)) {
		int input;
		int data_norm;
		v4l2_std_id norm;

		input = VINO_INPUT_COMPOSITE;

		ret = decoder_call(video, s_routing,
				vino_get_saa7191_input(input), 0, 0);
		if (ret) {
			ret = -EINVAL;
			goto out;
		}

		spin_unlock_irqrestore(&vino_drvdata->input_lock, flags);

		/* Don't hold spinlocks while auto-detecting norm
		 * as it may take a while... */

		ret = decoder_call(video, querystd, &norm);
		if (!ret) {
			for (data_norm = 0; data_norm < 3; data_norm++) {
				if (vino_data_norms[data_norm].std & norm)
					break;
			}
			if (data_norm == 3)
				data_norm = VINO_DATA_NORM_PAL;
			ret = decoder_call(core, s_std, norm);
		}

		spin_lock_irqsave(&vino_drvdata->input_lock, flags);

		if (ret) {
			ret = -EINVAL;
			goto out;
		}

		vino_drvdata->decoder_owner = vcs->channel;

		vcs->input = input;
		vcs->data_norm = data_norm;
	} else {
		vcs->input = (vcs->channel == VINO_CHANNEL_A) ?
			vino_drvdata->b.input : vino_drvdata->a.input;
		vcs->data_norm = (vcs->channel == VINO_CHANNEL_A) ?
			vino_drvdata->b.data_norm : vino_drvdata->a.data_norm;
	}

	if (vcs->input == VINO_INPUT_NONE) {
		ret = -ENODEV;
		goto out;
	}

	vino_set_default_clipping(vcs);
	vino_set_default_scaling(vcs);
	vino_set_default_framerate(vcs);

	dprintk("vino_acquire_input(): %s\n", vino_inputs[vcs->input].name);

out:
	spin_unlock_irqrestore(&vino_drvdata->input_lock, flags);

	return ret;
}