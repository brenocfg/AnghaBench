#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ gp2x_soc_t ;
struct TYPE_4__ {int frame_count; } ;
struct TYPE_6__ {TYPE_1__ m; } ;
struct TYPE_5__ {int volume; } ;

/* Variables and functions */
 int POPT_EN_STEREO ; 
 TYPE_3__ Pico ; 
 int PicoOpt ; 
 int /*<<< orphan*/  PsndMix_32_to_16l ; 
 scalar_t__ SOCID_MMSP2 ; 
 TYPE_2__ currentConfig ; 
 int /*<<< orphan*/  emu_status_msg (char*,int) ; 
 int mix_32_to_16l_level ; 
 int /*<<< orphan*/  mix_32_to_16l_stereo ; 
 int /*<<< orphan*/  mix_32_to_16l_stereo_lvl ; 
 int /*<<< orphan*/  plat_target_step_volume (int*,int) ; 
 scalar_t__ soc_detect () ; 

void plat_update_volume(int has_changed, int is_up)
{
	static int prev_frame = 0, wait_frames = 0;
	int need_low_volume = 0;
	int vol = currentConfig.volume;
	gp2x_soc_t soc;

	soc = soc_detect();
	if ((PicoOpt & POPT_EN_STEREO) && soc == SOCID_MMSP2)
		need_low_volume = 1;

	if (has_changed)
	{
		if (need_low_volume && vol < 5 && prev_frame == Pico.m.frame_count - 1 && wait_frames < 12)
			wait_frames++;
		else {
			wait_frames = 0;
			plat_target_step_volume(&currentConfig.volume, is_up ? 1 : -1);
			vol = currentConfig.volume;
		}
		emu_status_msg("VOL: %02i", vol);
		prev_frame = Pico.m.frame_count;
	}

	if (!need_low_volume)
		return;

	/* set the right mixer func */
	if (vol >= 5)
		PsndMix_32_to_16l = mix_32_to_16l_stereo;
	else {
		mix_32_to_16l_level = 5 - vol;
		PsndMix_32_to_16l = mix_32_to_16l_stereo_lvl;
	}
}