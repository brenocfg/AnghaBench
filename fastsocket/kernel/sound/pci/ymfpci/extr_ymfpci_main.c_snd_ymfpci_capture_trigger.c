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
typedef  int u32 ;
struct snd_ymfpci_pcm {int capture_bank_number; int running; } ;
struct snd_ymfpci {int /*<<< orphan*/  reg_lock; } ;
struct snd_pcm_substream {TYPE_1__* runtime; } ;
struct TYPE_2__ {struct snd_ymfpci_pcm* private_data; } ;

/* Variables and functions */
 int EINVAL ; 
#define  SNDRV_PCM_TRIGGER_PAUSE_PUSH 133 
#define  SNDRV_PCM_TRIGGER_PAUSE_RELEASE 132 
#define  SNDRV_PCM_TRIGGER_RESUME 131 
#define  SNDRV_PCM_TRIGGER_START 130 
#define  SNDRV_PCM_TRIGGER_STOP 129 
#define  SNDRV_PCM_TRIGGER_SUSPEND 128 
 int /*<<< orphan*/  YDSXGR_MAPOFREC ; 
 struct snd_ymfpci* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int snd_ymfpci_readl (struct snd_ymfpci*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_ymfpci_writel (struct snd_ymfpci*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_ymfpci_capture_trigger(struct snd_pcm_substream *substream,
				      int cmd)
{
	struct snd_ymfpci *chip = snd_pcm_substream_chip(substream);
	struct snd_ymfpci_pcm *ypcm = substream->runtime->private_data;
	int result = 0;
	u32 tmp;

	spin_lock(&chip->reg_lock);
	switch (cmd) {
	case SNDRV_PCM_TRIGGER_START:
	case SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
	case SNDRV_PCM_TRIGGER_RESUME:
		tmp = snd_ymfpci_readl(chip, YDSXGR_MAPOFREC) | (1 << ypcm->capture_bank_number);
		snd_ymfpci_writel(chip, YDSXGR_MAPOFREC, tmp);
		ypcm->running = 1;
		break;
	case SNDRV_PCM_TRIGGER_STOP:
	case SNDRV_PCM_TRIGGER_PAUSE_PUSH:
	case SNDRV_PCM_TRIGGER_SUSPEND:
		tmp = snd_ymfpci_readl(chip, YDSXGR_MAPOFREC) & ~(1 << ypcm->capture_bank_number);
		snd_ymfpci_writel(chip, YDSXGR_MAPOFREC, tmp);
		ypcm->running = 0;
		break;
	default:
		result = -EINVAL;
		break;
	}
	spin_unlock(&chip->reg_lock);
	return result;
}