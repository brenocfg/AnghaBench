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
struct snd_trident_voice {int ESO; int FMC; int GVSel; int Vol; int RVol; int CVol; int Pan; int Attribute; int isync2; int isync_mark; scalar_t__ FMS; scalar_t__ Alpha; scalar_t__ EC; int /*<<< orphan*/  CTRL; scalar_t__ CSO; int /*<<< orphan*/  LBA; int /*<<< orphan*/  spurious_threshold; int /*<<< orphan*/  Delta; TYPE_1__* memblk; struct snd_trident_voice* extra; } ;
struct snd_trident_pcm_mixer {int vol; int rvol; int cvol; int pan; } ;
struct snd_trident {scalar_t__ device; int /*<<< orphan*/  reg_lock; struct snd_trident_pcm_mixer* pcm_mixer; } ;
struct snd_pcm_substream {size_t number; struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {int period_size; int buffer_size; int /*<<< orphan*/  dma_addr; int /*<<< orphan*/  rate; struct snd_trident_voice* private_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  offset; } ;

/* Variables and functions */
 scalar_t__ TRIDENT_DEVICE_ID_SI7018 ; 
 struct snd_trident* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  snd_trident_control_mode (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  snd_trident_convert_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_trident_spurious_threshold (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snd_trident_write_voice_regs (struct snd_trident*,struct snd_trident_voice*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_trident_playback_prepare(struct snd_pcm_substream *substream)
{
	struct snd_trident *trident = snd_pcm_substream_chip(substream);
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct snd_trident_voice *voice = runtime->private_data;
	struct snd_trident_voice *evoice = voice->extra;
	struct snd_trident_pcm_mixer *mix = &trident->pcm_mixer[substream->number];

	spin_lock_irq(&trident->reg_lock);	

	/* set delta (rate) value */
	voice->Delta = snd_trident_convert_rate(runtime->rate);
	voice->spurious_threshold = snd_trident_spurious_threshold(runtime->rate, runtime->period_size);

	/* set Loop Begin Address */
	if (voice->memblk)
		voice->LBA = voice->memblk->offset;
	else
		voice->LBA = runtime->dma_addr;
 
	voice->CSO = 0;
	voice->ESO = runtime->buffer_size - 1;	/* in samples */
	voice->CTRL = snd_trident_control_mode(substream);
	voice->FMC = 3;
	voice->GVSel = 1;
	voice->EC = 0;
	voice->Alpha = 0;
	voice->FMS = 0;
	voice->Vol = mix->vol;
	voice->RVol = mix->rvol;
	voice->CVol = mix->cvol;
	voice->Pan = mix->pan;
	voice->Attribute = 0;
#if 0
	voice->Attribute = (1<<(30-16))|(2<<(26-16))|
			   (0<<(24-16))|(0x1f<<(19-16));
#else
	voice->Attribute = 0;
#endif

	snd_trident_write_voice_regs(trident, voice);

	if (evoice != NULL) {
		evoice->Delta = voice->Delta;
		evoice->spurious_threshold = voice->spurious_threshold;
		evoice->LBA = voice->LBA;
		evoice->CSO = 0;
		evoice->ESO = (runtime->period_size * 2) + 4 - 1; /* in samples */
		evoice->CTRL = voice->CTRL;
		evoice->FMC = 3;
		evoice->GVSel = trident->device == TRIDENT_DEVICE_ID_SI7018 ? 0 : 1;
		evoice->EC = 0;
		evoice->Alpha = 0;
		evoice->FMS = 0;
		evoice->Vol = 0x3ff;			/* mute */
		evoice->RVol = evoice->CVol = 0x7f;	/* mute */
		evoice->Pan = 0x7f;			/* mute */
#if 0
		evoice->Attribute = (1<<(30-16))|(2<<(26-16))|
				    (0<<(24-16))|(0x1f<<(19-16));
#else
		evoice->Attribute = 0;
#endif
		snd_trident_write_voice_regs(trident, evoice);
		evoice->isync2 = 1;
		evoice->isync_mark = runtime->period_size;
		evoice->ESO = (runtime->period_size * 2) - 1;
	}

	spin_unlock_irq(&trident->reg_lock);

	return 0;
}