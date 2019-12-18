#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int bytes; int fragsize; } ;
typedef  TYPE_1__ audio_buf_info ;

/* Variables and functions */
 int /*<<< orphan*/  SNDCTL_DSP_GETOSPACE ; 
 int /*<<< orphan*/  can_write_safe ; 
 int ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  sounddev ; 

int sndout_oss_can_write(int bytes)
{
	audio_buf_info bi;
	int ret;

#ifdef __GP2X__
	// note: SNDCTL_DSP_GETOSPACE crashes F100 kernel for some reason
	// if called too early, so we work around here
	if (can_write_safe++ < 8)
		return 1;
#endif
	ret = ioctl(sounddev, SNDCTL_DSP_GETOSPACE, &bi);
	if (ret < 0)
		return 1;

	// have enough bytes to write + 1 frag
	return bi.bytes - bi.fragsize >= bytes ? 1 : 0;
}