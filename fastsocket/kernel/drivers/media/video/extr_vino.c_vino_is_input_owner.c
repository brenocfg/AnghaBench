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
struct vino_channel_settings {int input; int /*<<< orphan*/  channel; } ;
struct TYPE_2__ {int /*<<< orphan*/  camera_owner; int /*<<< orphan*/  decoder_owner; } ;

/* Variables and functions */
#define  VINO_INPUT_COMPOSITE 130 
#define  VINO_INPUT_D1 129 
#define  VINO_INPUT_SVIDEO 128 
 TYPE_1__* vino_drvdata ; 

__attribute__((used)) static int vino_is_input_owner(struct vino_channel_settings *vcs)
{
	switch(vcs->input) {
	case VINO_INPUT_COMPOSITE:
	case VINO_INPUT_SVIDEO:
		return vino_drvdata->decoder_owner == vcs->channel;
	case VINO_INPUT_D1:
		return vino_drvdata->camera_owner == vcs->channel;
	default:
		return 0;
	}
}