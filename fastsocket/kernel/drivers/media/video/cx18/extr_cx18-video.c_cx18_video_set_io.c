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
struct cx18 {int active_input; TYPE_2__* card; int /*<<< orphan*/  sd_av; } ;
struct TYPE_4__ {TYPE_1__* video_inputs; } ;
struct TYPE_3__ {int /*<<< orphan*/  video_input; } ;

/* Variables and functions */
 int /*<<< orphan*/  s_routing ; 
 int /*<<< orphan*/  v4l2_subdev_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  video ; 

void cx18_video_set_io(struct cx18 *cx)
{
	int inp = cx->active_input;

	v4l2_subdev_call(cx->sd_av, video, s_routing,
			cx->card->video_inputs[inp].video_input, 0, 0);
}