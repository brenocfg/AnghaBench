#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 unsigned int VIDIOC_CROPCAP ; 
#define  VIDIOC_CROPCAP_OLD 133 
 unsigned int VIDIOC_G_AUDIO ; 
#define  VIDIOC_G_AUDIO_OLD 132 
 unsigned int VIDIOC_G_AUDOUT ; 
#define  VIDIOC_G_AUDOUT_OLD 131 
 unsigned int VIDIOC_OVERLAY ; 
#define  VIDIOC_OVERLAY_OLD 130 
 unsigned int VIDIOC_S_CTRL ; 
#define  VIDIOC_S_CTRL_OLD 129 
 unsigned int VIDIOC_S_PARM ; 
#define  VIDIOC_S_PARM_OLD 128 

__attribute__((used)) static unsigned int
video_fix_command(unsigned int cmd)
{
	switch (cmd) {
	case VIDIOC_OVERLAY_OLD:
		cmd = VIDIOC_OVERLAY;
		break;
	case VIDIOC_S_PARM_OLD:
		cmd = VIDIOC_S_PARM;
		break;
	case VIDIOC_S_CTRL_OLD:
		cmd = VIDIOC_S_CTRL;
		break;
	case VIDIOC_G_AUDIO_OLD:
		cmd = VIDIOC_G_AUDIO;
		break;
	case VIDIOC_G_AUDOUT_OLD:
		cmd = VIDIOC_G_AUDOUT;
		break;
	case VIDIOC_CROPCAP_OLD:
		cmd = VIDIOC_CROPCAP;
		break;
	}
	return cmd;
}