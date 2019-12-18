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
struct snd_pcm_runtime {struct mx1_mx2_runtime_data* private_data; } ;
struct mx1_mx2_runtime_data {int /*<<< orphan*/  dma_ch; } ;

/* Variables and functions */
 int /*<<< orphan*/  imx_dma_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_pcm_lib_free_pages (struct snd_pcm_substream*) ; 

__attribute__((used)) static int mx1_mx2_pcm_hw_free(struct snd_pcm_substream *substream)
{
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct mx1_mx2_runtime_data *prtd = runtime->private_data;

	imx_dma_free(prtd->dma_ch);

	snd_pcm_lib_free_pages(substream);

	return 0;
}