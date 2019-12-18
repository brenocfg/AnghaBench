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
struct snd_pcm_substream {struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {int /*<<< orphan*/  hw; int /*<<< orphan*/  private_free; struct snd_ca0106_pcm* private_data; } ;
struct snd_ca0106_pcm {int channel_id; struct snd_pcm_substream* substream; struct snd_ca0106* emu; } ;
struct snd_ca0106_channel {int number; int use; struct snd_ca0106_pcm* epcm; struct snd_ca0106* emu; } ;
struct snd_ca0106 {int /*<<< orphan*/ * spi_dac_reg; TYPE_1__* details; struct snd_ca0106_channel* playback_channels; } ;
struct TYPE_2__ {scalar_t__ spi_dac; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int PCM_FRONT_CHANNEL ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_PERIODS ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_PERIOD_BYTES ; 
 struct snd_ca0106_pcm* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  restore_spdif_bits (struct snd_ca0106*,int) ; 
 int /*<<< orphan*/  snd_ca0106_pcm_free_substream ; 
 int /*<<< orphan*/  snd_ca0106_playback_hw ; 
 int snd_ca0106_spi_write (struct snd_ca0106*,int /*<<< orphan*/ ) ; 
 int snd_pcm_hw_constraint_integer (struct snd_pcm_runtime*,int /*<<< orphan*/ ) ; 
 int snd_pcm_hw_constraint_step (struct snd_pcm_runtime*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snd_pcm_set_sync (struct snd_pcm_substream*) ; 
 struct snd_ca0106* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/ * spi_dacd_bit ; 
 int* spi_dacd_reg ; 

__attribute__((used)) static int snd_ca0106_pcm_open_playback_channel(struct snd_pcm_substream *substream,
						int channel_id)
{
	struct snd_ca0106 *chip = snd_pcm_substream_chip(substream);
        struct snd_ca0106_channel *channel = &(chip->playback_channels[channel_id]);
	struct snd_ca0106_pcm *epcm;
	struct snd_pcm_runtime *runtime = substream->runtime;
	int err;

	epcm = kzalloc(sizeof(*epcm), GFP_KERNEL);

	if (epcm == NULL)
		return -ENOMEM;
	epcm->emu = chip;
	epcm->substream = substream;
        epcm->channel_id=channel_id;
  
	runtime->private_data = epcm;
	runtime->private_free = snd_ca0106_pcm_free_substream;
  
	runtime->hw = snd_ca0106_playback_hw;

        channel->emu = chip;
        channel->number = channel_id;

	channel->use = 1;
	/*
	printk(KERN_DEBUG "open:channel_id=%d, chip=%p, channel=%p\n",
	       channel_id, chip, channel);
	*/
        //channel->interrupt = snd_ca0106_pcm_channel_interrupt;
	channel->epcm = epcm;
	if ((err = snd_pcm_hw_constraint_integer(runtime, SNDRV_PCM_HW_PARAM_PERIODS)) < 0)
                return err;
	if ((err = snd_pcm_hw_constraint_step(runtime, 0, SNDRV_PCM_HW_PARAM_PERIOD_BYTES, 64)) < 0)
                return err;
	snd_pcm_set_sync(substream);

	if (chip->details->spi_dac && channel_id != PCM_FRONT_CHANNEL) {
		const int reg = spi_dacd_reg[channel_id];

		/* Power up dac */
		chip->spi_dac_reg[reg] &= ~spi_dacd_bit[channel_id];
		err = snd_ca0106_spi_write(chip, chip->spi_dac_reg[reg]);
		if (err < 0)
			return err;
	}

	restore_spdif_bits(chip, channel_id);

	return 0;
}