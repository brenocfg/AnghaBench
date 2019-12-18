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
struct snd_pcm_substream {TYPE_1__* runtime; } ;
struct snd_als300_substream_data {unsigned short control_register; int period_flipflop; } ;
struct snd_als300 {int /*<<< orphan*/  reg_lock; int /*<<< orphan*/  port; } ;
struct TYPE_2__ {struct snd_als300_substream_data* private_data; } ;

/* Variables and functions */
 int EINVAL ; 
 int FIFO_PAUSE ; 
#define  SNDRV_PCM_TRIGGER_PAUSE_PUSH 133 
#define  SNDRV_PCM_TRIGGER_PAUSE_RELEASE 132 
#define  SNDRV_PCM_TRIGGER_RESUME 131 
#define  SNDRV_PCM_TRIGGER_START 130 
#define  SNDRV_PCM_TRIGGER_STOP 129 
#define  SNDRV_PCM_TRIGGER_SUSPEND 128 
 int TRANSFER_START ; 
 int /*<<< orphan*/  snd_als300_dbgcallenter () ; 
 int /*<<< orphan*/  snd_als300_dbgcallleave () ; 
 int /*<<< orphan*/  snd_als300_dbgplay (char*) ; 
 int snd_als300_gcr_read (int /*<<< orphan*/ ,unsigned short) ; 
 int /*<<< orphan*/  snd_als300_gcr_write (int /*<<< orphan*/ ,unsigned short,int) ; 
 struct snd_als300* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_als300_trigger(struct snd_pcm_substream *substream, int cmd)
{
	struct snd_als300 *chip = snd_pcm_substream_chip(substream);
	u32 tmp;
	struct snd_als300_substream_data *data;
	unsigned short reg;
	int ret = 0;

	data = substream->runtime->private_data;
	reg = data->control_register;

	snd_als300_dbgcallenter();
	spin_lock(&chip->reg_lock);
	switch (cmd) {
	case SNDRV_PCM_TRIGGER_START:
	case SNDRV_PCM_TRIGGER_RESUME:
		tmp = snd_als300_gcr_read(chip->port, reg);
		data->period_flipflop = 1;
		snd_als300_gcr_write(chip->port, reg, tmp | TRANSFER_START);
		snd_als300_dbgplay("TRIGGER START\n");
		break;
	case SNDRV_PCM_TRIGGER_STOP:
	case SNDRV_PCM_TRIGGER_SUSPEND:
		tmp = snd_als300_gcr_read(chip->port, reg);
		snd_als300_gcr_write(chip->port, reg, tmp & ~TRANSFER_START);
		snd_als300_dbgplay("TRIGGER STOP\n");
		break;
	case SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		tmp = snd_als300_gcr_read(chip->port, reg);
		snd_als300_gcr_write(chip->port, reg, tmp | FIFO_PAUSE);
		snd_als300_dbgplay("TRIGGER PAUSE\n");
		break;
	case SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		tmp = snd_als300_gcr_read(chip->port, reg);
		snd_als300_gcr_write(chip->port, reg, tmp & ~FIFO_PAUSE);
		snd_als300_dbgplay("TRIGGER RELEASE\n");
		break;
	default:
		snd_als300_dbgplay("TRIGGER INVALID\n");
		ret = -EINVAL;
	}
	spin_unlock(&chip->reg_lock);
	snd_als300_dbgcallleave();
	return ret;
}