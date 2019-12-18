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
struct TYPE_2__ {int /*<<< orphan*/  work; int /*<<< orphan*/  wq; } ;

/* Variables and functions */
 int /*<<< orphan*/  PS3AV_CMD_MUTE_ON ; 
 TYPE_1__* ps3av ; 
 int /*<<< orphan*/  ps3av_set_av_video_mute (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ps3av_set_videomode(void)
{
	/* av video mute */
	ps3av_set_av_video_mute(PS3AV_CMD_MUTE_ON);

	/* wake up ps3avd to do the actual video mode setting */
	queue_work(ps3av->wq, &ps3av->work);

	return 0;
}