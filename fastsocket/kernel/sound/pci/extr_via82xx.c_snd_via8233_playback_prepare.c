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
typedef  int u32 ;
struct viadev {int reg_offset; } ;
struct via82xx {int /*<<< orphan*/ ** playback_volume; int /*<<< orphan*/  ac97; scalar_t__ spdif_on; scalar_t__ no_vra; int /*<<< orphan*/ * rates; scalar_t__ dxs_src; } ;
struct snd_pcm_substream {struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {int rate; scalar_t__ format; int channels; struct viadev* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  AC97_PCM_FRONT_DAC_RATE ; 
 int /*<<< orphan*/  AC97_SPDIF ; 
 int /*<<< orphan*/  OFFSET_STOP_IDX ; 
 int /*<<< orphan*/  OFS_PLAYBACK_VOLUME_L ; 
 int /*<<< orphan*/  OFS_PLAYBACK_VOLUME_R ; 
 scalar_t__ SNDRV_PCM_FORMAT_S16_LE ; 
 int VIA8233_REG_TYPE_16BIT ; 
 int VIA8233_REG_TYPE_STEREO ; 
 int /*<<< orphan*/  VIADEV_REG (struct viadev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outl (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_BUG_ON (int) ; 
 int /*<<< orphan*/  snd_ac97_set_rate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct via82xx* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  snd_via82xx_channel_reset (struct via82xx*,struct viadev*) ; 
 int /*<<< orphan*/  snd_via82xx_codec_ready (struct via82xx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_via82xx_set_table_ptr (struct via82xx*,struct viadev*) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int via_lock_rate (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int snd_via8233_playback_prepare(struct snd_pcm_substream *substream)
{
	struct via82xx *chip = snd_pcm_substream_chip(substream);
	struct viadev *viadev = substream->runtime->private_data;
	struct snd_pcm_runtime *runtime = substream->runtime;
	int ac97_rate = chip->dxs_src ? 48000 : runtime->rate;
	int rate_changed;
	u32 rbits;

	if ((rate_changed = via_lock_rate(&chip->rates[0], ac97_rate)) < 0)
		return rate_changed;
	if (rate_changed)
		snd_ac97_set_rate(chip->ac97, AC97_PCM_FRONT_DAC_RATE,
				  chip->no_vra ? 48000 : runtime->rate);
	if (chip->spdif_on && viadev->reg_offset == 0x30)
		snd_ac97_set_rate(chip->ac97, AC97_SPDIF, runtime->rate);

	if (runtime->rate == 48000)
		rbits = 0xfffff;
	else
		rbits = (0x100000 / 48000) * runtime->rate +
			((0x100000 % 48000) * runtime->rate) / 48000;
	snd_BUG_ON(rbits & ~0xfffff);
	snd_via82xx_channel_reset(chip, viadev);
	snd_via82xx_set_table_ptr(chip, viadev);
	outb(chip->playback_volume[viadev->reg_offset / 0x10][0],
	     VIADEV_REG(viadev, OFS_PLAYBACK_VOLUME_L));
	outb(chip->playback_volume[viadev->reg_offset / 0x10][1],
	     VIADEV_REG(viadev, OFS_PLAYBACK_VOLUME_R));
	outl((runtime->format == SNDRV_PCM_FORMAT_S16_LE ? VIA8233_REG_TYPE_16BIT : 0) | /* format */
	     (runtime->channels > 1 ? VIA8233_REG_TYPE_STEREO : 0) | /* stereo */
	     rbits | /* rate */
	     0xff000000,    /* STOP index is never reached */
	     VIADEV_REG(viadev, OFFSET_STOP_IDX));
	udelay(20);
	snd_via82xx_codec_ready(chip, 0);
	return 0;
}