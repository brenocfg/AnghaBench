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
struct vino_channel_settings {int input; } ;
typedef  int __u32 ;
struct TYPE_2__ {scalar_t__ camera; scalar_t__ decoder; } ;

/* Variables and functions */
#define  VINO_INPUT_COMPOSITE 130 
#define  VINO_INPUT_D1 129 
#define  VINO_INPUT_SVIDEO 128 
 TYPE_1__* vino_drvdata ; 

__attribute__((used)) static __u32 vino_find_input_index(struct vino_channel_settings *vcs)
{
	__u32 index = 0;
	// FIXME: detect when no inputs available

	if (vino_drvdata->decoder && vino_drvdata->camera) {
		switch (vcs->input) {
		case VINO_INPUT_COMPOSITE:
			index = 0;
			break;
		case VINO_INPUT_SVIDEO:
			index = 1;
			break;
		case VINO_INPUT_D1:
			index = 2;
			break;
		}
	} else if (vino_drvdata->decoder) {
		switch (vcs->input) {
		case VINO_INPUT_COMPOSITE:
			index = 0;
			break;
		case VINO_INPUT_SVIDEO:
			index = 1;
			break;
		}
	} else if (vino_drvdata->camera) {
		switch (vcs->input) {
		case VINO_INPUT_D1:
			index = 0;
			break;
		}
	}

	return index;
}