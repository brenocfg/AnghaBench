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
struct snd_pcm_substream {TYPE_2__* pcm; struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {struct pxa2xx_runtime_data* private_data; } ;
struct pxa2xx_runtime_data {int /*<<< orphan*/  dma_desc_array_phys; int /*<<< orphan*/  dma_desc_array; } ;
struct TYPE_4__ {TYPE_1__* card; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  dma_free_writecombine (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct pxa2xx_runtime_data*) ; 

int __pxa2xx_pcm_close(struct snd_pcm_substream *substream)
{
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct pxa2xx_runtime_data *rtd = runtime->private_data;

	dma_free_writecombine(substream->pcm->card->dev, PAGE_SIZE,
			      rtd->dma_desc_array, rtd->dma_desc_array_phys);
	kfree(rtd);
	return 0;
}