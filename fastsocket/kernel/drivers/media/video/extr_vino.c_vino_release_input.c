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
struct vino_channel_settings {scalar_t__ channel; scalar_t__ input; } ;
struct TYPE_2__ {scalar_t__ camera_owner; scalar_t__ decoder_owner; int /*<<< orphan*/  input_lock; struct vino_channel_settings a; struct vino_channel_settings b; } ;

/* Variables and functions */
 scalar_t__ VINO_CHANNEL_A ; 
 scalar_t__ VINO_INPUT_COMPOSITE ; 
 scalar_t__ VINO_INPUT_D1 ; 
 scalar_t__ VINO_INPUT_NONE ; 
 scalar_t__ VINO_INPUT_SVIDEO ; 
 void* VINO_NO_CHANNEL ; 
 int /*<<< orphan*/  dprintk (char*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 TYPE_1__* vino_drvdata ; 

__attribute__((used)) static void vino_release_input(struct vino_channel_settings *vcs)
{
	struct vino_channel_settings *vcs2 = (vcs->channel == VINO_CHANNEL_A) ?
		&vino_drvdata->b : &vino_drvdata->a;
	unsigned long flags;

	dprintk("vino_release_input():\n");

	spin_lock_irqsave(&vino_drvdata->input_lock, flags);

	/* Release ownership of the channel
	 * and if the other channel takes input from
	 * the same source, transfer the ownership */
	if (vino_drvdata->camera_owner == vcs->channel) {
		if (vcs2->input == VINO_INPUT_D1) {
			vino_drvdata->camera_owner = vcs2->channel;
		} else {
			vino_drvdata->camera_owner = VINO_NO_CHANNEL;
		}
	} else if (vino_drvdata->decoder_owner == vcs->channel) {
		if ((vcs2->input == VINO_INPUT_COMPOSITE) ||
			 (vcs2->input == VINO_INPUT_SVIDEO)) {
			vino_drvdata->decoder_owner = vcs2->channel;
		} else {
			vino_drvdata->decoder_owner = VINO_NO_CHANNEL;
		}
	}
	vcs->input = VINO_INPUT_NONE;

	spin_unlock_irqrestore(&vino_drvdata->input_lock, flags);
}