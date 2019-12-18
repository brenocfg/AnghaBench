#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct snd_emu10k1 {int tos_link; scalar_t__ port; TYPE_1__* card_capabilities; scalar_t__ audigy; } ;
struct TYPE_2__ {scalar_t__ ca0108_chip; scalar_t__ ca0151_chip; scalar_t__ i2c_adc; scalar_t__ emu_model; } ;

/* Variables and functions */
 scalar_t__ A_IOCFG ; 
 scalar_t__ HCFG ; 
 unsigned int HCFG_AUDIOENABLE ; 
 unsigned int HCFG_GPINPUT0 ; 
 unsigned int HCFG_GPINPUT1 ; 
 int /*<<< orphan*/  INTE_PCIERRORENABLE ; 
 int inl (scalar_t__) ; 
 int /*<<< orphan*/  outl (unsigned int,scalar_t__) ; 
 int /*<<< orphan*/  snd_emu10k1_intr_enable (struct snd_emu10k1*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void snd_emu10k1_audio_enable(struct snd_emu10k1 *emu)
{
	/*
	 *  Enable the audio bit
	 */
	outl(inl(emu->port + HCFG) | HCFG_AUDIOENABLE, emu->port + HCFG);

	/* Enable analog/digital outs on audigy */
	if (emu->card_capabilities->emu_model) {
		;  /* Disable all access to A_IOCFG for the emu1010 */
	} else if (emu->card_capabilities->i2c_adc) {
		;  /* Disable A_IOCFG for Audigy 2 ZS Notebook */
	} else if (emu->audigy) {
		outl(inl(emu->port + A_IOCFG) & ~0x44, emu->port + A_IOCFG);

		if (emu->card_capabilities->ca0151_chip) { /* audigy2 */
			/* Unmute Analog now.  Set GPO6 to 1 for Apollo.
			 * This has to be done after init ALice3 I2SOut beyond 48KHz.
			 * So, sequence is important. */
			outl(inl(emu->port + A_IOCFG) | 0x0040, emu->port + A_IOCFG);
		} else if (emu->card_capabilities->ca0108_chip) { /* audigy2 value */
			/* Unmute Analog now. */
			outl(inl(emu->port + A_IOCFG) | 0x0060, emu->port + A_IOCFG);
		} else {
			/* Disable routing from AC97 line out to Front speakers */
			outl(inl(emu->port + A_IOCFG) | 0x0080, emu->port + A_IOCFG);
		}
	}

#if 0
	{
	unsigned int tmp;
	/* FIXME: the following routine disables LiveDrive-II !! */
	/* TOSLink detection */
	emu->tos_link = 0;
	tmp = inl(emu->port + HCFG);
	if (tmp & (HCFG_GPINPUT0 | HCFG_GPINPUT1)) {
		outl(tmp|0x800, emu->port + HCFG);
		udelay(50);
		if (tmp != (inl(emu->port + HCFG) & ~0x800)) {
			emu->tos_link = 1;
			outl(tmp, emu->port + HCFG);
		}
	}
	}
#endif

	snd_emu10k1_intr_enable(emu, INTE_PCIERRORENABLE);
}