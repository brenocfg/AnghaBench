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
 void* SCALE (unsigned int,unsigned int) ; 
#define  SOUND_MIXER_PCM 129 
#define  SOUND_MIXER_VOLUME 128 
 void* vidc_audio_volume_l ; 
 void* vidc_audio_volume_r ; 
 unsigned int* vidc_level_l ; 
 unsigned int* vidc_level_r ; 

__attribute__((used)) static void
vidc_mixer_set(int mdev, unsigned int level)
{
	unsigned int lev_l = level & 0x007f;
	unsigned int lev_r = (level & 0x7f00) >> 8;
	unsigned int mlev_l, mlev_r;

	if (lev_l > 100)
		lev_l = 100;
	if (lev_r > 100)
		lev_r = 100;

#define SCALE(lev,master)	((lev) * (master) * 65536 / 10000)

	mlev_l = vidc_level_l[SOUND_MIXER_VOLUME];
	mlev_r = vidc_level_r[SOUND_MIXER_VOLUME];

	switch (mdev) {
	case SOUND_MIXER_VOLUME:
	case SOUND_MIXER_PCM:
		vidc_level_l[mdev] = lev_l;
		vidc_level_r[mdev] = lev_r;

		vidc_audio_volume_l = SCALE(lev_l, mlev_l);
		vidc_audio_volume_r = SCALE(lev_r, mlev_r);
/*printk("VIDC: PCM vol %05X %05X\n", vidc_audio_volume_l, vidc_audio_volume_r);*/
		break;
	}
#undef SCALE
}