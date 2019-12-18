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
 int /*<<< orphan*/  SOUND_MIXER_WRITE_PCM ; 
 int /*<<< orphan*/  ioctl (scalar_t__,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ mixerdev ; 

void sndout_oss_setvol(int l, int r)
{
	if (mixerdev < 0) return;

 	l=l<0?0:l; l=l>255?255:l; r=r<0?0:r; r=r>255?255:r;
 	l<<=8; l|=r;
 	ioctl(mixerdev, SOUND_MIXER_WRITE_PCM, &l); /*SOUND_MIXER_WRITE_VOLUME*/
}