#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct snd_pcm_substream {size_t number; struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {unsigned int buffer_size; unsigned int period_size; } ;
struct TYPE_4__ {int hw_buffer_size; int /*<<< orphan*/  sw_buffer_size; } ;
struct snd_emu10k1_fx8010_pcm {int buffer_size; unsigned int channels; scalar_t__* etram; scalar_t__ gpr_tmpcount; scalar_t__ gpr_count; scalar_t__ gpr_ptr; scalar_t__ gpr_size; scalar_t__ gpr_trigger; scalar_t__ gpr_running; scalar_t__ tram_shift; int /*<<< orphan*/  tram_pos; TYPE_2__ pcm_rec; } ;
struct TYPE_3__ {struct snd_emu10k1_fx8010_pcm* pcm; } ;
struct snd_emu10k1 {scalar_t__ gpr_base; TYPE_1__ fx8010; } ;

/* Variables and functions */
 int /*<<< orphan*/  INITIAL_TRAM_POS (int) ; 
 scalar_t__ TANKMEMADDRREGBASE ; 
 unsigned int TANKMEMADDRREG_ALIGN ; 
 unsigned int TANKMEMADDRREG_READ ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snd_emu10k1_ptr_write (struct snd_emu10k1*,scalar_t__,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  snd_pcm_lib_buffer_bytes (struct snd_pcm_substream*) ; 
 struct snd_emu10k1* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static int snd_emu10k1_fx8010_playback_prepare(struct snd_pcm_substream *substream)
{
	struct snd_emu10k1 *emu = snd_pcm_substream_chip(substream);
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct snd_emu10k1_fx8010_pcm *pcm = &emu->fx8010.pcm[substream->number];
	unsigned int i;
	
	/*
	printk(KERN_DEBUG "prepare: etram_pages = 0x%p, dma_area = 0x%x, "
	       "buffer_size = 0x%x (0x%x)\n",
	       emu->fx8010.etram_pages, runtime->dma_area,
	       runtime->buffer_size, runtime->buffer_size << 2);
	*/
	memset(&pcm->pcm_rec, 0, sizeof(pcm->pcm_rec));
	pcm->pcm_rec.hw_buffer_size = pcm->buffer_size * 2; /* byte size */
	pcm->pcm_rec.sw_buffer_size = snd_pcm_lib_buffer_bytes(substream);
	pcm->tram_pos = INITIAL_TRAM_POS(pcm->buffer_size);
	pcm->tram_shift = 0;
	snd_emu10k1_ptr_write(emu, emu->gpr_base + pcm->gpr_running, 0, 0);	/* reset */
	snd_emu10k1_ptr_write(emu, emu->gpr_base + pcm->gpr_trigger, 0, 0);	/* reset */
	snd_emu10k1_ptr_write(emu, emu->gpr_base + pcm->gpr_size, 0, runtime->buffer_size);
	snd_emu10k1_ptr_write(emu, emu->gpr_base + pcm->gpr_ptr, 0, 0);		/* reset ptr number */
	snd_emu10k1_ptr_write(emu, emu->gpr_base + pcm->gpr_count, 0, runtime->period_size);
	snd_emu10k1_ptr_write(emu, emu->gpr_base + pcm->gpr_tmpcount, 0, runtime->period_size);
	for (i = 0; i < pcm->channels; i++)
		snd_emu10k1_ptr_write(emu, TANKMEMADDRREGBASE + 0x80 + pcm->etram[i], 0, (TANKMEMADDRREG_READ|TANKMEMADDRREG_ALIGN) + i * (runtime->buffer_size / pcm->channels));
	return 0;
}