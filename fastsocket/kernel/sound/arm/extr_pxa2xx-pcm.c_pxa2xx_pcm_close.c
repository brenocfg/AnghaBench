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
struct snd_pcm_substream {TYPE_1__* runtime; struct pxa2xx_pcm_client* private_data; } ;
struct pxa2xx_runtime_data {int /*<<< orphan*/  dma_ch; } ;
struct pxa2xx_pcm_client {int /*<<< orphan*/  (* shutdown ) (struct snd_pcm_substream*) ;} ;
struct TYPE_2__ {struct pxa2xx_runtime_data* private_data; } ;

/* Variables and functions */
 int __pxa2xx_pcm_close (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  pxa_free_dma (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct snd_pcm_substream*) ; 

__attribute__((used)) static int pxa2xx_pcm_close(struct snd_pcm_substream *substream)
{
	struct pxa2xx_pcm_client *client = substream->private_data;
	struct pxa2xx_runtime_data *rtd = substream->runtime->private_data;

	pxa_free_dma(rtd->dma_ch);
	client->shutdown(substream);

	return __pxa2xx_pcm_close(substream);
}