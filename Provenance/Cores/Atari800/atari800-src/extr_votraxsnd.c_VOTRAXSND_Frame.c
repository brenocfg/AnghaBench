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
 scalar_t__ Atari800_TV_PAL ; 
 scalar_t__ Atari800_tv_mode ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  PBI_XLD_votrax_busy_callback (int /*<<< orphan*/ ) ; 
 double* POKEY_AUDF ; 
 double VOICEBOX_BASEAUDF ; 
 scalar_t__ VOICEBOX_enabled ; 
 scalar_t__ VOICEBOX_ii ; 
 int /*<<< orphan*/  VOTRAXSND_busy ; 
 scalar_t__ VTRX_RATE ; 
 scalar_t__ dsprate ; 
 double ratio ; 
 double samples_per_frame ; 
 scalar_t__ votrax_sync_samples ; 
 int /*<<< orphan*/  votraxsnd_enabled () ; 

void VOTRAXSND_Frame(void)
{
	if (!votraxsnd_enabled()) return;
#ifdef VOICEBOX
	if (VOICEBOX_enabled && VOICEBOX_ii) {
		double factor = (VOICEBOX_BASEAUDF+1.0)/(POKEY_AUDF[3]+1.0);
		ratio = (double)VTRX_RATE/(double)dsprate * factor;
		samples_per_frame = ((double)dsprate/(double)(Atari800_tv_mode == Atari800_TV_PAL ? 50 : 60)) / factor;
	}
#endif
	votrax_sync_samples -= samples_per_frame;
	if (votrax_sync_samples <= 0 ) {
		votrax_sync_samples = 0;
		VOTRAXSND_busy = FALSE;
#ifdef PBI_XLD
		PBI_XLD_votrax_busy_callback(FALSE); /* busy -> idle */
#endif
	}
}