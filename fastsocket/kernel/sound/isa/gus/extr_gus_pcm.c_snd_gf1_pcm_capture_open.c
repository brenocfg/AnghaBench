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
struct snd_pcm_substream {struct snd_pcm_runtime* runtime; } ;
struct TYPE_4__ {int /*<<< orphan*/  period_bytes_max; int /*<<< orphan*/  buffer_bytes_max; } ;
struct snd_pcm_runtime {TYPE_2__ hw; } ;
struct TYPE_3__ {int /*<<< orphan*/  dma2; int /*<<< orphan*/  interrupt_handler_dma_read; } ;
struct snd_gus_card {TYPE_1__ gf1; struct snd_pcm_substream* pcm_cap_substream; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_RATE ; 
 int /*<<< orphan*/  hw_constraints_clocks ; 
 TYPE_2__ snd_gf1_pcm_capture ; 
 int /*<<< orphan*/  snd_gf1_pcm_interrupt_dma_read ; 
 int /*<<< orphan*/  snd_pcm_hw_constraint_ratnums (struct snd_pcm_runtime*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_pcm_limit_isa_dma_size (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct snd_gus_card* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static int snd_gf1_pcm_capture_open(struct snd_pcm_substream *substream)
{
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct snd_gus_card *gus = snd_pcm_substream_chip(substream);

	gus->gf1.interrupt_handler_dma_read = snd_gf1_pcm_interrupt_dma_read;
	gus->pcm_cap_substream = substream;
	substream->runtime->hw = snd_gf1_pcm_capture;
	snd_pcm_limit_isa_dma_size(gus->gf1.dma2, &runtime->hw.buffer_bytes_max);
	snd_pcm_limit_isa_dma_size(gus->gf1.dma2, &runtime->hw.period_bytes_max);
	snd_pcm_hw_constraint_ratnums(runtime, 0, SNDRV_PCM_HW_PARAM_RATE,
				      &hw_constraints_clocks);
	return 0;
}