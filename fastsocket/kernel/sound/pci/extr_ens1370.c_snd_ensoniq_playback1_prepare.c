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
struct snd_pcm_substream {struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {int channels; int rate; int dma_addr; int /*<<< orphan*/  format; } ;
struct ensoniq {int p1_dma_size; int p1_period_size; int ctrl; int sctrl; int /*<<< orphan*/  reg_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONTROL ; 
 int /*<<< orphan*/  DAC1_COUNT ; 
 int /*<<< orphan*/  DAC1_FRAME ; 
 int /*<<< orphan*/  DAC1_SIZE ; 
 int ES_1370_WTSRSEL (int) ; 
 int ES_1370_WTSRSELM ; 
 int ES_1373_BYPASS_P1 ; 
 int ES_DAC1_EN ; 
 int ES_MEM_PAGEO (int /*<<< orphan*/ ) ; 
 int ES_P1_INT_EN ; 
 int ES_P1_LOOP_SEL ; 
 int ES_P1_MODEM ; 
 int ES_P1_MODEO (unsigned int) ; 
 int ES_P1_PAUSE ; 
 int ES_P1_SCT_RLD ; 
 int /*<<< orphan*/  ES_PAGE_DAC ; 
 int /*<<< orphan*/  ES_REG (struct ensoniq*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MEM_PAGE ; 
 int /*<<< orphan*/  SERIAL ; 
 int /*<<< orphan*/  outl (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_BUG () ; 
 int* snd_ensoniq_sample_shift ; 
 int /*<<< orphan*/  snd_es1371_dac1_rate (struct ensoniq*,int) ; 
 int snd_pcm_format_width (int /*<<< orphan*/ ) ; 
 int snd_pcm_lib_buffer_bytes (struct snd_pcm_substream*) ; 
 int snd_pcm_lib_period_bytes (struct snd_pcm_substream*) ; 
 struct ensoniq* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_ensoniq_playback1_prepare(struct snd_pcm_substream *substream)
{
	struct ensoniq *ensoniq = snd_pcm_substream_chip(substream);
	struct snd_pcm_runtime *runtime = substream->runtime;
	unsigned int mode = 0;

	ensoniq->p1_dma_size = snd_pcm_lib_buffer_bytes(substream);
	ensoniq->p1_period_size = snd_pcm_lib_period_bytes(substream);
	if (snd_pcm_format_width(runtime->format) == 16)
		mode |= 0x02;
	if (runtime->channels > 1)
		mode |= 0x01;
	spin_lock_irq(&ensoniq->reg_lock);
	ensoniq->ctrl &= ~ES_DAC1_EN;
#ifdef CHIP1371
	/* 48k doesn't need SRC (it breaks AC3-passthru) */
	if (runtime->rate == 48000)
		ensoniq->ctrl |= ES_1373_BYPASS_P1;
	else
		ensoniq->ctrl &= ~ES_1373_BYPASS_P1;
#endif
	outl(ensoniq->ctrl, ES_REG(ensoniq, CONTROL));
	outl(ES_MEM_PAGEO(ES_PAGE_DAC), ES_REG(ensoniq, MEM_PAGE));
	outl(runtime->dma_addr, ES_REG(ensoniq, DAC1_FRAME));
	outl((ensoniq->p1_dma_size >> 2) - 1, ES_REG(ensoniq, DAC1_SIZE));
	ensoniq->sctrl &= ~(ES_P1_LOOP_SEL | ES_P1_PAUSE | ES_P1_SCT_RLD | ES_P1_MODEM);
	ensoniq->sctrl |= ES_P1_INT_EN | ES_P1_MODEO(mode);
	outl(ensoniq->sctrl, ES_REG(ensoniq, SERIAL));
	outl((ensoniq->p1_period_size >> snd_ensoniq_sample_shift[mode]) - 1,
	     ES_REG(ensoniq, DAC1_COUNT));
#ifdef CHIP1370
	ensoniq->ctrl &= ~ES_1370_WTSRSELM;
	switch (runtime->rate) {
	case 5512: ensoniq->ctrl |= ES_1370_WTSRSEL(0); break;
	case 11025: ensoniq->ctrl |= ES_1370_WTSRSEL(1); break;
	case 22050: ensoniq->ctrl |= ES_1370_WTSRSEL(2); break;
	case 44100: ensoniq->ctrl |= ES_1370_WTSRSEL(3); break;
	default: snd_BUG();
	}
#endif
	outl(ensoniq->ctrl, ES_REG(ensoniq, CONTROL));
	spin_unlock_irq(&ensoniq->reg_lock);
#ifndef CHIP1370
	snd_es1371_dac1_rate(ensoniq, runtime->rate);
#endif
	return 0;
}