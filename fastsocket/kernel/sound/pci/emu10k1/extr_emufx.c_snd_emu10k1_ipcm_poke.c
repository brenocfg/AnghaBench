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
struct snd_emu10k1_fx8010_pcm_rec {size_t substream; int channels; int /*<<< orphan*/ * etram; int /*<<< orphan*/  gpr_running; int /*<<< orphan*/  gpr_trigger; int /*<<< orphan*/  gpr_ptr; int /*<<< orphan*/  gpr_tmpcount; int /*<<< orphan*/  gpr_count; int /*<<< orphan*/  gpr_size; int /*<<< orphan*/  buffer_size; int /*<<< orphan*/  tram_start; } ;
struct snd_emu10k1_fx8010_pcm {int valid; unsigned int channels; int /*<<< orphan*/ * etram; int /*<<< orphan*/  gpr_running; int /*<<< orphan*/  gpr_trigger; int /*<<< orphan*/  gpr_ptr; int /*<<< orphan*/  gpr_tmpcount; int /*<<< orphan*/  gpr_count; int /*<<< orphan*/  gpr_size; int /*<<< orphan*/  buffer_size; int /*<<< orphan*/  tram_start; scalar_t__ opened; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; struct snd_emu10k1_fx8010_pcm* pcm; } ;
struct snd_emu10k1 {TYPE_1__ fx8010; int /*<<< orphan*/  reg_lock; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 size_t EMU10K1_FX8010_PCM_COUNT ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_emu10k1_ipcm_poke(struct snd_emu10k1 *emu,
				 struct snd_emu10k1_fx8010_pcm_rec *ipcm)
{
	unsigned int i;
	int err = 0;
	struct snd_emu10k1_fx8010_pcm *pcm;

	if (ipcm->substream >= EMU10K1_FX8010_PCM_COUNT)
		return -EINVAL;
	if (ipcm->channels > 32)
		return -EINVAL;
	pcm = &emu->fx8010.pcm[ipcm->substream];
	mutex_lock(&emu->fx8010.lock);
	spin_lock_irq(&emu->reg_lock);
	if (pcm->opened) {
		err = -EBUSY;
		goto __error;
	}
	if (ipcm->channels == 0) {	/* remove */
		pcm->valid = 0;
	} else {
		/* FIXME: we need to add universal code to the PCM transfer routine */
		if (ipcm->channels != 2) {
			err = -EINVAL;
			goto __error;
		}
		pcm->valid = 1;
		pcm->opened = 0;
		pcm->channels = ipcm->channels;
		pcm->tram_start = ipcm->tram_start;
		pcm->buffer_size = ipcm->buffer_size;
		pcm->gpr_size = ipcm->gpr_size;
		pcm->gpr_count = ipcm->gpr_count;
		pcm->gpr_tmpcount = ipcm->gpr_tmpcount;
		pcm->gpr_ptr = ipcm->gpr_ptr;
		pcm->gpr_trigger = ipcm->gpr_trigger;
		pcm->gpr_running = ipcm->gpr_running;
		for (i = 0; i < pcm->channels; i++)
			pcm->etram[i] = ipcm->etram[i];
	}
      __error:
	spin_unlock_irq(&emu->reg_lock);
	mutex_unlock(&emu->fx8010.lock);
	return err;
}