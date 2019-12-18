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
 scalar_t__ Atari800_TV_NTSC ; 
 scalar_t__ Atari800_tv_mode ; 
 int /*<<< orphan*/  POKEYSND_Process (char*,unsigned int) ; 
 int /*<<< orphan*/  audsrv_play_audio (char*,unsigned int) ; 
 int /*<<< orphan*/  audsrv_wait_audio (unsigned int) ; 

void Sound_Update(void)
{
	static char buffer[44100 / 50];
	unsigned int nsamples = (Atari800_tv_mode == Atari800_TV_NTSC) ? (44100 / 60) : (44100 / 50);
	POKEYSND_Process(buffer, nsamples);
	audsrv_wait_audio(nsamples);
	audsrv_play_audio(buffer, nsamples);
}