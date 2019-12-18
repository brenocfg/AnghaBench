#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  name; } ;
struct TYPE_9__ {TYPE_1__ hw; } ;
typedef  TYPE_2__ wavnc_info ;

/* Variables and functions */
 int DEBUG_MIXER ; 
 int SOUND_MIXER_NRDEVICES ; 
 int /*<<< orphan*/  WACMD_RST_MIXER ; 
 int /*<<< orphan*/  WACMD_SET_MIXER ; 
 int debug_flg ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  waveartist_cmd1 (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  waveartist_cmd3 (TYPE_2__*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  waveartist_mixer_update (TYPE_2__*,int) ; 
 int /*<<< orphan*/  waveartist_set_recmask (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
waveartist_mixer_reset(wavnc_info *devc)
{
	int i;

	if (debug_flg & DEBUG_MIXER)
		printk("%s: mixer_reset\n", devc->hw.name);

	/*
	 * reset mixer cmd
	 */
	waveartist_cmd1(devc, WACMD_RST_MIXER);

	/*
	 * set input for ADC to come from 'quiet'
	 * turn on default modes
	 */
	waveartist_cmd3(devc, WACMD_SET_MIXER, 0x9800, 0xa836);

	/*
	 * set mixer input select to none, RX filter gains 0 dB
	 */
	waveartist_cmd3(devc, WACMD_SET_MIXER, 0x4c00, 0x8c00);

	/*
	 * set bit 0 reg 2 to 1 - unmute MonoOut
	 */
	waveartist_cmd3(devc, WACMD_SET_MIXER, 0x2801, 0x6800);

	/* set default input device = internal mic
	 * current recording device = none
	 */
	waveartist_set_recmask(devc, 0);

	for (i = 0; i < SOUND_MIXER_NRDEVICES; i++)
		waveartist_mixer_update(devc, i);
}