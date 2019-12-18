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
struct TYPE_3__ {unsigned char* levels; } ;
typedef  TYPE_1__ wavnc_info ;

/* Variables and functions */
 int EINVAL ; 
#define  SOUND_MIXER_IGAIN 136 
#define  SOUND_MIXER_IMIX 135 
#define  SOUND_MIXER_LINE 134 
#define  SOUND_MIXER_LINE1 133 
#define  SOUND_MIXER_LINE2 132 
#define  SOUND_MIXER_MIC 131 
#define  SOUND_MIXER_PCM 130 
#define  SOUND_MIXER_SYNTH 129 
#define  SOUND_MIXER_VOLUME 128 

__attribute__((used)) static int
waveartist_decode_mixer(wavnc_info *devc, int dev, unsigned char lev_l,
			unsigned char lev_r)
{
	switch (dev) {
	case SOUND_MIXER_VOLUME:
	case SOUND_MIXER_SYNTH:
	case SOUND_MIXER_PCM:
	case SOUND_MIXER_LINE:
	case SOUND_MIXER_MIC:
	case SOUND_MIXER_IGAIN:
	case SOUND_MIXER_LINE1:
	case SOUND_MIXER_LINE2:
		devc->levels[dev] = lev_l | lev_r << 8;
		break;

	case SOUND_MIXER_IMIX:
		break;

	default:
		dev = -EINVAL;
		break;
	}

	return dev;
}