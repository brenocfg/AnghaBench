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
struct cx231xx {int video_input; int /*<<< orphan*/  ctl_ainput; } ;
struct TYPE_2__ {int /*<<< orphan*/  vmux; int /*<<< orphan*/  amux; } ;

/* Variables and functions */
 TYPE_1__* INPUT (int) ; 
 int /*<<< orphan*/  cx231xx_do_mode_ctrl_overrides (struct cx231xx*) ; 
 int /*<<< orphan*/  cx231xx_info (char*,int) ; 
 int /*<<< orphan*/  cx231xx_set_audio_input (struct cx231xx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cx231xx_set_video_input_mux (struct cx231xx*,int) ; 
 int /*<<< orphan*/  cx25840_call (struct cx231xx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s_routing ; 
 int /*<<< orphan*/  video ; 

void video_mux(struct cx231xx *dev, int index)
{
	dev->video_input = index;
	dev->ctl_ainput = INPUT(index)->amux;

	cx231xx_set_video_input_mux(dev, index);

	cx25840_call(dev, video, s_routing, INPUT(index)->vmux, 0, 0);

	cx231xx_set_audio_input(dev, dev->ctl_ainput);

	cx231xx_info("video_mux : %d\n", index);

	/* do mode control overrides if required */
	cx231xx_do_mode_ctrl_overrides(dev);
}