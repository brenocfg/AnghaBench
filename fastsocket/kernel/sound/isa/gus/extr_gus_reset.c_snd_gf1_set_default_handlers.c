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
struct snd_gus_voice {int /*<<< orphan*/ * volume_change; int /*<<< orphan*/ * handler_effect; int /*<<< orphan*/  handler_volume; int /*<<< orphan*/  handler_wave; } ;
struct TYPE_2__ {int /*<<< orphan*/  interrupt_handler_dma_read; int /*<<< orphan*/  interrupt_handler_dma_write; struct snd_gus_voice* voices; int /*<<< orphan*/  interrupt_handler_timer2; int /*<<< orphan*/  interrupt_handler_timer1; int /*<<< orphan*/  interrupt_handler_midi_in; int /*<<< orphan*/  interrupt_handler_midi_out; } ;
struct snd_gus_card {TYPE_1__ gf1; } ;

/* Variables and functions */
 unsigned int SNDRV_GF1_HANDLER_DMA_READ ; 
 unsigned int SNDRV_GF1_HANDLER_DMA_WRITE ; 
 unsigned int SNDRV_GF1_HANDLER_MIDI_IN ; 
 unsigned int SNDRV_GF1_HANDLER_MIDI_OUT ; 
 unsigned int SNDRV_GF1_HANDLER_TIMER1 ; 
 unsigned int SNDRV_GF1_HANDLER_TIMER2 ; 
 unsigned int SNDRV_GF1_HANDLER_VOICE ; 
 int /*<<< orphan*/  snd_gf1_default_interrupt_handler_dma_read ; 
 int /*<<< orphan*/  snd_gf1_default_interrupt_handler_dma_write ; 
 int /*<<< orphan*/  snd_gf1_default_interrupt_handler_midi_in ; 
 int /*<<< orphan*/  snd_gf1_default_interrupt_handler_midi_out ; 
 int /*<<< orphan*/  snd_gf1_default_interrupt_handler_timer1 ; 
 int /*<<< orphan*/  snd_gf1_default_interrupt_handler_timer2 ; 
 int /*<<< orphan*/  snd_gf1_default_interrupt_handler_wave_and_volume ; 

void snd_gf1_set_default_handlers(struct snd_gus_card * gus, unsigned int what)
{
	if (what & SNDRV_GF1_HANDLER_MIDI_OUT)
		gus->gf1.interrupt_handler_midi_out = snd_gf1_default_interrupt_handler_midi_out;
	if (what & SNDRV_GF1_HANDLER_MIDI_IN)
		gus->gf1.interrupt_handler_midi_in = snd_gf1_default_interrupt_handler_midi_in;
	if (what & SNDRV_GF1_HANDLER_TIMER1)
		gus->gf1.interrupt_handler_timer1 = snd_gf1_default_interrupt_handler_timer1;
	if (what & SNDRV_GF1_HANDLER_TIMER2)
		gus->gf1.interrupt_handler_timer2 = snd_gf1_default_interrupt_handler_timer2;
	if (what & SNDRV_GF1_HANDLER_VOICE) {
		struct snd_gus_voice *voice;
		
		voice = &gus->gf1.voices[what & 0xffff];
		voice->handler_wave =
		voice->handler_volume = snd_gf1_default_interrupt_handler_wave_and_volume;
		voice->handler_effect = NULL;
		voice->volume_change = NULL;
	}
	if (what & SNDRV_GF1_HANDLER_DMA_WRITE)
		gus->gf1.interrupt_handler_dma_write = snd_gf1_default_interrupt_handler_dma_write;
	if (what & SNDRV_GF1_HANDLER_DMA_READ)
		gus->gf1.interrupt_handler_dma_read = snd_gf1_default_interrupt_handler_dma_read;
}