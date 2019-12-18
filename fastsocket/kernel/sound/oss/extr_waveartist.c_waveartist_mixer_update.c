#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int* levels; } ;
typedef  TYPE_1__ wavnc_info ;
struct mix_ent {int reg_l; int reg_r; unsigned int max; unsigned int shift; } ;

/* Variables and functions */
 unsigned int SCALE (unsigned int,int) ; 
#define  SOUND_MIXER_PCM 129 
 int SOUND_MIXER_PHONEOUT ; 
#define  SOUND_MIXER_SYNTH 128 
 int SOUND_MIXER_VOLUME ; 
 int WACMD_GET_LEVEL ; 
 int WACMD_SET_LEVEL ; 
 int WACMD_SET_MIXER ; 
 scalar_t__ machine_is_netwinder () ; 
 struct mix_ent* mix_devs ; 
 unsigned int waveartist_cmd1_r (TYPE_1__*,int) ; 
 int /*<<< orphan*/  waveartist_cmd3 (TYPE_1__*,int,unsigned int,unsigned int) ; 

__attribute__((used)) static void
waveartist_mixer_update(wavnc_info *devc, int whichDev)
{
	unsigned int lev_left, lev_right;

	lev_left  = devc->levels[whichDev] & 0xff;
	lev_right = devc->levels[whichDev] >> 8;

	if (lev_left > 100)
		lev_left = 100;
	if (lev_right > 100)
		lev_right = 100;

#define SCALE(lev,max)	((lev) * (max) / 100)

	if (machine_is_netwinder() && whichDev == SOUND_MIXER_PHONEOUT)
		whichDev = SOUND_MIXER_VOLUME;

	if (mix_devs[whichDev].reg_l || mix_devs[whichDev].reg_r) {
		const struct mix_ent *mix = mix_devs + whichDev;
		unsigned int mask, left, right;

		mask = mix->max << mix->shift;
		lev_left  = SCALE(lev_left,  mix->max) << mix->shift;
		lev_right = SCALE(lev_right, mix->max) << mix->shift;

		/* read left setting */
		left  = waveartist_cmd1_r(devc, WACMD_GET_LEVEL |
					       mix->reg_l << 8);

		/* read right setting */
		right = waveartist_cmd1_r(devc, WACMD_GET_LEVEL |
						mix->reg_r << 8);

		left  = (left  & ~mask) | (lev_left  & mask);
		right = (right & ~mask) | (lev_right & mask);

		/* write left,right back */
		waveartist_cmd3(devc, WACMD_SET_MIXER, left, right);
	} else {
		switch(whichDev) {
		case SOUND_MIXER_PCM:
			waveartist_cmd3(devc, WACMD_SET_LEVEL,
					SCALE(lev_left,  32767),
					SCALE(lev_right, 32767));
			break;

		case SOUND_MIXER_SYNTH:
			waveartist_cmd3(devc, 0x0100 | WACMD_SET_LEVEL,
					SCALE(lev_left,  32767),
					SCALE(lev_right, 32767));
			break;
		}
	}
}