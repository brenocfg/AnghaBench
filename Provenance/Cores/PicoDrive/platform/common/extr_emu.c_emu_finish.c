#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ changed; } ;
struct TYPE_3__ {int EmuOpt; } ;

/* Variables and functions */
 int EOPT_EN_SRAM ; 
 int EOPT_NO_AUTOSVCFG ; 
 int /*<<< orphan*/  PicoExit () ; 
 TYPE_2__ SRam ; 
 int /*<<< orphan*/  config_writelrom (char*) ; 
 TYPE_1__ currentConfig ; 
 int /*<<< orphan*/  emu_save_load_game (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  make_config_cfg (char*) ; 
 int /*<<< orphan*/  pprof_finish () ; 
 int /*<<< orphan*/  sndout_exit () ; 
 int /*<<< orphan*/  sync () ; 

void emu_finish(void)
{
	// save SRAM
	if ((currentConfig.EmuOpt & EOPT_EN_SRAM) && SRam.changed) {
		emu_save_load_game(0, 1);
		SRam.changed = 0;
	}

	if (!(currentConfig.EmuOpt & EOPT_NO_AUTOSVCFG)) {
		char cfg[512];
		make_config_cfg(cfg);
		config_writelrom(cfg);
#ifdef __GP2X__
		sync();
#endif
	}

	pprof_finish();

	PicoExit();
	sndout_exit();
}