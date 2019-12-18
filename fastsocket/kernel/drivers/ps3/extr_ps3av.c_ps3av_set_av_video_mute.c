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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_3__ {int num_of_hdmi; int num_of_avmulti; } ;
struct TYPE_4__ {int /*<<< orphan*/ * av_port; TYPE_1__ av_hw_conf; } ;

/* Variables and functions */
 TYPE_2__* ps3av ; 
 int ps3av_cmd_av_video_mute (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ps3av_set_av_video_mute(u32 mute)
{
	int i, num_of_av_port, res;

	num_of_av_port = ps3av->av_hw_conf.num_of_hdmi +
			 ps3av->av_hw_conf.num_of_avmulti;
	/* video mute on */
	for (i = 0; i < num_of_av_port; i++) {
		res = ps3av_cmd_av_video_mute(1, &ps3av->av_port[i], mute);
		if (res < 0)
			return -1;
	}

	return 0;
}