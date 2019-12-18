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
struct snd_pcm_substream {int dummy; } ;
struct intel8x0m {int dummy; } ;
struct ichdev {unsigned long reg_offset; scalar_t__ roff_sr; } ;

/* Variables and functions */
 int EINVAL ; 
 int ICH_DCH ; 
 unsigned char ICH_IOCE ; 
 scalar_t__ ICH_REG_OFF_CR ; 
 unsigned char ICH_RESETREGS ; 
 unsigned char ICH_STARTBM ; 
#define  SNDRV_PCM_TRIGGER_PAUSE_PUSH 133 
#define  SNDRV_PCM_TRIGGER_PAUSE_RELEASE 132 
#define  SNDRV_PCM_TRIGGER_RESUME 131 
#define  SNDRV_PCM_TRIGGER_START 130 
#define  SNDRV_PCM_TRIGGER_STOP 129 
#define  SNDRV_PCM_TRIGGER_SUSPEND 128 
 struct ichdev* get_ichdev (struct snd_pcm_substream*) ; 
 int igetbyte (struct intel8x0m*,scalar_t__) ; 
 int /*<<< orphan*/  iputbyte (struct intel8x0m*,scalar_t__,unsigned char) ; 
 struct intel8x0m* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static int snd_intel8x0_pcm_trigger(struct snd_pcm_substream *substream, int cmd)
{
	struct intel8x0m *chip = snd_pcm_substream_chip(substream);
	struct ichdev *ichdev = get_ichdev(substream);
	unsigned char val = 0;
	unsigned long port = ichdev->reg_offset;

	switch (cmd) {
	case SNDRV_PCM_TRIGGER_START:
	case SNDRV_PCM_TRIGGER_RESUME:
		val = ICH_IOCE | ICH_STARTBM;
		break;
	case SNDRV_PCM_TRIGGER_STOP:
	case SNDRV_PCM_TRIGGER_SUSPEND:
		val = 0;
		break;
	case SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		val = ICH_IOCE;
		break;
	case SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		val = ICH_IOCE | ICH_STARTBM;
		break;
	default:
		return -EINVAL;
	}
	iputbyte(chip, port + ICH_REG_OFF_CR, val);
	if (cmd == SNDRV_PCM_TRIGGER_STOP) {
		/* wait until DMA stopped */
		while (!(igetbyte(chip, port + ichdev->roff_sr) & ICH_DCH)) ;
		/* reset whole DMA things */
		iputbyte(chip, port + ICH_REG_OFF_CR, ICH_RESETREGS);
	}
	return 0;
}