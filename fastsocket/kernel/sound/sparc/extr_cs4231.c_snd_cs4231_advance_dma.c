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
struct snd_pcm_runtime {unsigned int periods; scalar_t__ dma_addr; } ;
struct cs4231_dma_control {scalar_t__ (* request ) (struct cs4231_dma_control*,scalar_t__,unsigned int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 unsigned int snd_pcm_lib_period_bytes (struct snd_pcm_substream*) ; 
 scalar_t__ stub1 (struct cs4231_dma_control*,scalar_t__,unsigned int) ; 

__attribute__((used)) static void snd_cs4231_advance_dma(struct cs4231_dma_control *dma_cont,
				   struct snd_pcm_substream *substream,
				   unsigned int *periods_sent)
{
	struct snd_pcm_runtime *runtime = substream->runtime;

	while (1) {
		unsigned int period_size = snd_pcm_lib_period_bytes(substream);
		unsigned int offset = period_size * (*periods_sent);

		BUG_ON(period_size >= (1 << 24));

		if (dma_cont->request(dma_cont,
				      runtime->dma_addr + offset, period_size))
			return;
		(*periods_sent) = ((*periods_sent) + 1) % runtime->periods;
	}
}