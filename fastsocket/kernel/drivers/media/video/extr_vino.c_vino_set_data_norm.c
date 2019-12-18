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
typedef  int /*<<< orphan*/  v4l2_std_id ;
struct vino_channel_settings {unsigned int data_norm; int input; } ;
struct TYPE_4__ {int /*<<< orphan*/  std; } ;
struct TYPE_3__ {int /*<<< orphan*/  input_lock; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int VINO_DATA_NORM_D1 ; 
 unsigned int VINO_DATA_NORM_NTSC ; 
 unsigned int VINO_DATA_NORM_PAL ; 
 unsigned int VINO_DATA_NORM_SECAM ; 
#define  VINO_INPUT_COMPOSITE 130 
#define  VINO_INPUT_D1 129 
#define  VINO_INPUT_SVIDEO 128 
 int /*<<< orphan*/  core ; 
 int decoder_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s_std ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 TYPE_2__* vino_data_norms ; 
 TYPE_1__* vino_drvdata ; 
 int /*<<< orphan*/  vino_set_default_clipping (struct vino_channel_settings*) ; 
 int /*<<< orphan*/  vino_set_default_framerate (struct vino_channel_settings*) ; 
 int /*<<< orphan*/  vino_set_default_scaling (struct vino_channel_settings*) ; 

__attribute__((used)) static int vino_set_data_norm(struct vino_channel_settings *vcs,
			      unsigned int data_norm,
			      unsigned long *flags)
{
	int err = 0;

	if (data_norm == vcs->data_norm)
		return 0;

	switch (vcs->input) {
	case VINO_INPUT_D1:
		/* only one "norm" supported */
		if (data_norm != VINO_DATA_NORM_D1)
			return -EINVAL;
		break;
	case VINO_INPUT_COMPOSITE:
	case VINO_INPUT_SVIDEO: {
		v4l2_std_id norm;

		if ((data_norm != VINO_DATA_NORM_PAL)
		    && (data_norm != VINO_DATA_NORM_NTSC)
		    && (data_norm != VINO_DATA_NORM_SECAM))
			return -EINVAL;

		spin_unlock_irqrestore(&vino_drvdata->input_lock, *flags);

		/* Don't hold spinlocks while setting norm
		 * as it may take a while... */

		norm = vino_data_norms[data_norm].std;
		err = decoder_call(core, s_std, norm);

		spin_lock_irqsave(&vino_drvdata->input_lock, *flags);

		if (err)
			goto out;

		vcs->data_norm = data_norm;

		vino_set_default_clipping(vcs);
		vino_set_default_scaling(vcs);
		vino_set_default_framerate(vcs);
		break;
	}
	default:
		return -EINVAL;
	}

out:
	return err;
}