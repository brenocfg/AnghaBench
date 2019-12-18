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
struct snd_ac97 {int flags; int ext_id; TYPE_1__* bus; } ;
struct TYPE_2__ {scalar_t__ no_vra; } ;

/* Variables and functions */
 int AC97_DOUBLE_RATE ; 
 int /*<<< orphan*/  AC97_EA_DRA ; 
 int AC97_EI_DRA ; 
 int /*<<< orphan*/  AC97_EXTENDED_STATUS ; 
 int AC97_PCM_FRONT_DAC_RATE ; 
 unsigned int SNDRV_PCM_RATE_11025 ; 
 unsigned int SNDRV_PCM_RATE_16000 ; 
 unsigned int SNDRV_PCM_RATE_22050 ; 
 unsigned int SNDRV_PCM_RATE_32000 ; 
 unsigned int SNDRV_PCM_RATE_44100 ; 
 unsigned int SNDRV_PCM_RATE_48000 ; 
 unsigned int SNDRV_PCM_RATE_64000 ; 
 unsigned int SNDRV_PCM_RATE_8000 ; 
 unsigned int SNDRV_PCM_RATE_88200 ; 
 unsigned int SNDRV_PCM_RATE_96000 ; 
 unsigned int SNDRV_PCM_RATE_CONTINUOUS ; 
 unsigned short snd_ac97_read (struct snd_ac97*,int) ; 
 scalar_t__ snd_ac97_test_rate (struct snd_ac97*,int,int,int) ; 
 int /*<<< orphan*/  snd_ac97_update_bits (struct snd_ac97*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_ac97_write_cache (struct snd_ac97*,int,unsigned short) ; 

__attribute__((used)) static void snd_ac97_determine_rates(struct snd_ac97 *ac97, int reg, int shadow_reg, unsigned int *r_result)
{
	unsigned int result = 0;
	unsigned short saved;

	if (ac97->bus->no_vra) {
		*r_result = SNDRV_PCM_RATE_48000;
		if ((ac97->flags & AC97_DOUBLE_RATE) &&
		    reg == AC97_PCM_FRONT_DAC_RATE)
			*r_result |= SNDRV_PCM_RATE_96000;
		return;
	}

	saved = snd_ac97_read(ac97, reg);
	if ((ac97->ext_id & AC97_EI_DRA) && reg == AC97_PCM_FRONT_DAC_RATE)
		snd_ac97_update_bits(ac97, AC97_EXTENDED_STATUS,
				     AC97_EA_DRA, 0);
	/* test a non-standard rate */
	if (snd_ac97_test_rate(ac97, reg, shadow_reg, 11000))
		result |= SNDRV_PCM_RATE_CONTINUOUS;
	/* let's try to obtain standard rates */
	if (snd_ac97_test_rate(ac97, reg, shadow_reg, 8000))
		result |= SNDRV_PCM_RATE_8000;
	if (snd_ac97_test_rate(ac97, reg, shadow_reg, 11025))
		result |= SNDRV_PCM_RATE_11025;
	if (snd_ac97_test_rate(ac97, reg, shadow_reg, 16000))
		result |= SNDRV_PCM_RATE_16000;
	if (snd_ac97_test_rate(ac97, reg, shadow_reg, 22050))
		result |= SNDRV_PCM_RATE_22050;
	if (snd_ac97_test_rate(ac97, reg, shadow_reg, 32000))
		result |= SNDRV_PCM_RATE_32000;
	if (snd_ac97_test_rate(ac97, reg, shadow_reg, 44100))
		result |= SNDRV_PCM_RATE_44100;
	if (snd_ac97_test_rate(ac97, reg, shadow_reg, 48000))
		result |= SNDRV_PCM_RATE_48000;
	if ((ac97->flags & AC97_DOUBLE_RATE) &&
	    reg == AC97_PCM_FRONT_DAC_RATE) {
		/* test standard double rates */
		snd_ac97_update_bits(ac97, AC97_EXTENDED_STATUS,
				     AC97_EA_DRA, AC97_EA_DRA);
		if (snd_ac97_test_rate(ac97, reg, shadow_reg, 64000 / 2))
			result |= SNDRV_PCM_RATE_64000;
		if (snd_ac97_test_rate(ac97, reg, shadow_reg, 88200 / 2))
			result |= SNDRV_PCM_RATE_88200;
		if (snd_ac97_test_rate(ac97, reg, shadow_reg, 96000 / 2))
			result |= SNDRV_PCM_RATE_96000;
		/* some codecs don't support variable double rates */
		if (!snd_ac97_test_rate(ac97, reg, shadow_reg, 76100 / 2))
			result &= ~SNDRV_PCM_RATE_CONTINUOUS;
		snd_ac97_update_bits(ac97, AC97_EXTENDED_STATUS,
				     AC97_EA_DRA, 0);
	}
	/* restore the default value */
	snd_ac97_write_cache(ac97, reg, saved);
	if (shadow_reg)
		snd_ac97_write_cache(ac97, shadow_reg, saved);
	*r_result = result;
}