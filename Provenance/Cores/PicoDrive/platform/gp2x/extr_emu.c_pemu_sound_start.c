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
struct TYPE_4__ {scalar_t__ frame_count; } ;
struct TYPE_6__ {TYPE_1__ m; } ;
struct TYPE_5__ {int EmuOpt; int /*<<< orphan*/  volume; } ;

/* Variables and functions */
 int EOPT_EN_SOUND ; 
 TYPE_3__ Pico ; 
 int /*<<< orphan*/  PsndRate ; 
 int /*<<< orphan*/  PsndRerate (int) ; 
 scalar_t__ SOCID_POLLUX ; 
 TYPE_2__ currentConfig ; 
 int /*<<< orphan*/  emu_sound_start () ; 
 int /*<<< orphan*/  plat_target_step_volume (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pollux_get_real_snd_rate (int /*<<< orphan*/ ) ; 
 scalar_t__ soc_detect () ; 

void pemu_sound_start(void)
{
	gp2x_soc_t soc;

	emu_sound_start();

	if (currentConfig.EmuOpt & EOPT_EN_SOUND)
	{
		soc = soc_detect();
		if (soc == SOCID_POLLUX) {
			PsndRate = pollux_get_real_snd_rate(PsndRate);
			PsndRerate(Pico.m.frame_count ? 1 : 0);
		}

		plat_target_step_volume(&currentConfig.volume, 0);
	}
}