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
struct snd_pcm_runtime {int dma_bytes; int /*<<< orphan*/ * dma_area; } ;
struct snd_pcm_hw_params {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int params_buffer_bytes (struct snd_pcm_hw_params*) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vmalloc_user (int) ; 

__attribute__((used)) static int snd_sgio2audio_pcm_hw_params(struct snd_pcm_substream *substream,
					struct snd_pcm_hw_params *hw_params)
{
	struct snd_pcm_runtime *runtime = substream->runtime;
	int size = params_buffer_bytes(hw_params);

	/* alloc virtual 'dma' area */
	if (runtime->dma_area)
		vfree(runtime->dma_area);
	runtime->dma_area = vmalloc_user(size);
	if (runtime->dma_area == NULL)
		return -ENOMEM;
	runtime->dma_bytes = size;
	return 0;
}