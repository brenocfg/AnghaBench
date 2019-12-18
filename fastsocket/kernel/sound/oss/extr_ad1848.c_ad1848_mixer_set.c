#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int supported_devices; int* mixer_reroute; int* levels; TYPE_1__** mix_devices; } ;
typedef  TYPE_2__ ad1848_info ;
struct TYPE_5__ {scalar_t__ nbits; } ;

/* Variables and functions */
 int EINVAL ; 
 size_t LEFT_CHN ; 
 size_t RIGHT_CHN ; 
 int /*<<< orphan*/  ad1848_mixer_set_channel (TYPE_2__*,int,int,size_t) ; 
 int* mix_cvt ; 

__attribute__((used)) static int ad1848_mixer_set(ad1848_info * devc, int dev, int value)
{
	int left = value & 0x000000ff;
	int right = (value & 0x0000ff00) >> 8;
	int retvol;

	if (dev > 31)
		return -EINVAL;

	if (!(devc->supported_devices & (1 << dev)))
		return -EINVAL;

	dev = devc->mixer_reroute[dev];

	if (devc->mix_devices[dev][LEFT_CHN].nbits == 0)
		return -EINVAL;

	if (left > 100)
		left = 100;
	if (right > 100)
		right = 100;

	if (devc->mix_devices[dev][RIGHT_CHN].nbits == 0)	/* Mono control */
		right = left;

	retvol = left | (right << 8);

	/* Scale volumes */
	left = mix_cvt[left];
	right = mix_cvt[right];

	devc->levels[dev] = retvol;

	/*
	 * Set the left channel
	 */
	ad1848_mixer_set_channel(devc, dev, left, LEFT_CHN);

	/*
	 * Set the right channel
	 */
	if (devc->mix_devices[dev][RIGHT_CHN].nbits == 0)
		goto out;
	ad1848_mixer_set_channel(devc, dev, right, RIGHT_CHN);

 out:
	return retvol;
}