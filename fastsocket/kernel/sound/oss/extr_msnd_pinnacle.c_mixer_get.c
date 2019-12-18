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
struct TYPE_2__ {int* left_levels; int* right_levels; } ;

/* Variables and functions */
 int EINVAL ; 
#define  SOUND_MIXER_IMIX 134 
#define  SOUND_MIXER_LINE 133 
#define  SOUND_MIXER_LINE1 132 
#define  SOUND_MIXER_MIC 131 
#define  SOUND_MIXER_PCM 130 
#define  SOUND_MIXER_SYNTH 129 
#define  SOUND_MIXER_VOLUME 128 
 TYPE_1__ dev ; 

__attribute__((used)) static int mixer_get(int d)
{
	if (d > 31)
		return -EINVAL;

	switch (d) {
	case SOUND_MIXER_VOLUME:
	case SOUND_MIXER_PCM:
	case SOUND_MIXER_LINE:
	case SOUND_MIXER_IMIX:
	case SOUND_MIXER_LINE1:
#ifndef MSND_CLASSIC
	case SOUND_MIXER_MIC:
	case SOUND_MIXER_SYNTH:
#endif
		return (dev.left_levels[d] >> 8) * 100 / 0xff | 
			(((dev.right_levels[d] >> 8) * 100 / 0xff) << 8);
	default:
		return 0;
	}
}