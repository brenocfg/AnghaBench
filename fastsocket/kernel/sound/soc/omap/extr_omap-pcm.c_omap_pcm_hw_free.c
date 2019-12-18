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
struct snd_pcm_runtime {struct omap_runtime_data* private_data; } ;
struct omap_runtime_data {int /*<<< orphan*/ * dma_data; int /*<<< orphan*/  dma_ch; } ;

/* Variables and functions */
 int /*<<< orphan*/  omap_dma_unlink_lch (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap_free_dma (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_pcm_set_runtime_buffer (struct snd_pcm_substream*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int omap_pcm_hw_free(struct snd_pcm_substream *substream)
{
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct omap_runtime_data *prtd = runtime->private_data;

	if (prtd->dma_data == NULL)
		return 0;

	omap_dma_unlink_lch(prtd->dma_ch, prtd->dma_ch);
	omap_free_dma(prtd->dma_ch);
	prtd->dma_data = NULL;

	snd_pcm_set_runtime_buffer(substream, NULL);

	return 0;
}