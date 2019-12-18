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
struct TYPE_2__ {int /*<<< orphan*/ * dma_data_synth_last; int /*<<< orphan*/  dma_data_pcm_last; struct snd_gf1_dma_block* dma_data_synth; struct snd_gf1_dma_block* dma_data_pcm; int /*<<< orphan*/  dma1; int /*<<< orphan*/  dma_shared; } ;
struct snd_gus_card {int /*<<< orphan*/  dma_mutex; TYPE_1__ gf1; } ;
struct snd_gf1_dma_block {struct snd_gf1_dma_block* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_GF1_HANDLER_DMA_WRITE ; 
 int /*<<< orphan*/  kfree (struct snd_gf1_dma_block*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_dma_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_gf1_dma_ack (struct snd_gus_card*) ; 
 int /*<<< orphan*/  snd_gf1_set_default_handlers (struct snd_gus_card*,int /*<<< orphan*/ ) ; 

int snd_gf1_dma_done(struct snd_gus_card * gus)
{
	struct snd_gf1_dma_block *block;

	mutex_lock(&gus->dma_mutex);
	gus->gf1.dma_shared--;
	if (!gus->gf1.dma_shared) {
		snd_dma_disable(gus->gf1.dma1);
		snd_gf1_set_default_handlers(gus, SNDRV_GF1_HANDLER_DMA_WRITE);
		snd_gf1_dma_ack(gus);
		while ((block = gus->gf1.dma_data_pcm)) {
			gus->gf1.dma_data_pcm = block->next;
			kfree(block);
		}
		while ((block = gus->gf1.dma_data_synth)) {
			gus->gf1.dma_data_synth = block->next;
			kfree(block);
		}
		gus->gf1.dma_data_pcm_last =
		gus->gf1.dma_data_synth_last = NULL;
	}
	mutex_unlock(&gus->dma_mutex);
	return 0;
}