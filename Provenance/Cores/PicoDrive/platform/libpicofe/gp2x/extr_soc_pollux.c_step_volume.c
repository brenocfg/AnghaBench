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
 int ioctl (scalar_t__,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ mixerdev ; 
 int /*<<< orphan*/  perror (char*) ; 

__attribute__((used)) static int step_volume(int *volume, int diff)
{
	int ret, val;

	if (mixerdev < 0)
		return -1;

	*volume += diff;
	if (*volume > 255)
		*volume = 255;
	else if (*volume < 0)
		*volume = 0;

	val = *volume;
	val |= val << 8;

 	ret = ioctl(mixerdev, SOUND_MIXER_WRITE_PCM, &val);
	if (ret == -1) {
		perror("WRITE_PCM");
		return ret;
	}

	return 0;
}