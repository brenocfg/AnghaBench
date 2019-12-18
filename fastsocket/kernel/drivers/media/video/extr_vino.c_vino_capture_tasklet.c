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
struct TYPE_3__ {scalar_t__ skip_count; scalar_t__ skip; } ;
struct vino_channel_settings {TYPE_1__ int_data; } ;
struct TYPE_4__ {struct vino_channel_settings b; struct vino_channel_settings a; } ;

/* Variables and functions */
 unsigned long VINO_CHANNEL_A ; 
 scalar_t__ VINO_MAX_FRAME_SKIP_COUNT ; 
 TYPE_2__* vino_drvdata ; 
 int /*<<< orphan*/  vino_frame_done (struct vino_channel_settings*) ; 
 int /*<<< orphan*/  vino_skip_frame (struct vino_channel_settings*) ; 

__attribute__((used)) static void vino_capture_tasklet(unsigned long channel) {
	struct vino_channel_settings *vcs;

	vcs = (channel == VINO_CHANNEL_A)
		? &vino_drvdata->a : &vino_drvdata->b;

	if (vcs->int_data.skip)
		vcs->int_data.skip_count++;

	if (vcs->int_data.skip && (vcs->int_data.skip_count
				   <= VINO_MAX_FRAME_SKIP_COUNT)) {
		vino_skip_frame(vcs);
	} else {
		vcs->int_data.skip_count = 0;
		vino_frame_done(vcs);
	}
}