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
struct snd_soc_dai {struct snd_soc_codec* codec; } ;
struct snd_soc_codec {int dummy; } ;
struct snd_pcm_substream {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AC97_EXTENDED_STATUS ; 
#define  SNDRV_PCM_TRIGGER_STOP 128 
 unsigned short stac9766_ac97_read (struct snd_soc_codec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stac9766_ac97_write (struct snd_soc_codec*,int /*<<< orphan*/ ,unsigned short) ; 

__attribute__((used)) static int ac97_digital_trigger(struct snd_pcm_substream *substream,
				int cmd, struct snd_soc_dai *dai)
{
	struct snd_soc_codec *codec = dai->codec;
	unsigned short vra;

	switch (cmd) {
	case SNDRV_PCM_TRIGGER_STOP:
		vra = stac9766_ac97_read(codec, AC97_EXTENDED_STATUS);
		vra &= !0x04;
		stac9766_ac97_write(codec, AC97_EXTENDED_STATUS, vra);
		break;
	}
	return 0;
}