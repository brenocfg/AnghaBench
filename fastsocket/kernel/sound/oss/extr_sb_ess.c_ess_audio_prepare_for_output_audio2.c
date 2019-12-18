#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_7__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int channels; scalar_t__ bits; scalar_t__ trigger_bits; } ;
typedef  TYPE_1__ sb_devc ;
struct TYPE_9__ {TYPE_1__* devc; } ;

/* Variables and functions */
 scalar_t__ AFMT_U8 ; 
 int /*<<< orphan*/  SOUND_MIXER_PCM ; 
 TYPE_7__** audio_devs ; 
 int /*<<< orphan*/  ess_chgmixer (TYPE_1__*,int,int,int) ; 
 int ess_getmixer (TYPE_1__*,int) ; 
 int /*<<< orphan*/  ess_mixer_reload (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ess_setmixer (TYPE_1__*,int,unsigned char) ; 
 int /*<<< orphan*/  ess_speed (TYPE_1__*,int) ; 

__attribute__((used)) static int ess_audio_prepare_for_output_audio2 (int dev, int bsize, int bcount)
{
	sb_devc *devc = audio_devs[dev]->devc;
	unsigned char bits;

/* FKS: qqq
	sb_dsp_reset(devc);
*/

	/*
	 * Auto-Initialize:
	 * DMA mode + demand mode (8 bytes/request, yes I want it all!)
	 * But leave 16-bit DMA bit untouched!
	 */
	ess_chgmixer (devc, 0x78, 0xd0, 0xd0);

	ess_speed(devc, 2);

	/* bits 4:3 on ES1887 represent recording source. Keep them! */
	bits = ess_getmixer (devc, 0x7a) & 0x18;

	/* Set stereo/mono */
	if (devc->channels != 1) bits |= 0x02;

	/* Init DACs; UNSIGNED mode for 8 bit; SIGNED mode for 16 bit */
	if (devc->bits != AFMT_U8) bits |= 0x05;	/* 16 bit */

	/* Enable DMA, IRQ will be shared (hopefully)*/
	bits |= 0x60;

	ess_setmixer (devc, 0x7a, bits);

	ess_mixer_reload (devc, SOUND_MIXER_PCM);	/* There be sound! */

	devc->trigger_bits = 0;
	return 0;
}