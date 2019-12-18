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
struct snd_pcm_runtime {int dma_bytes; int /*<<< orphan*/  period_size; scalar_t__ dma_area; struct aaci_runtime* private_data; } ;
struct aaci_runtime {int /*<<< orphan*/  bytes; int /*<<< orphan*/  period; void* start; void* ptr; void* end; } ;

/* Variables and functions */
 int /*<<< orphan*/  frames_to_bytes (struct snd_pcm_runtime*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int aaci_pcm_prepare(struct snd_pcm_substream *substream)
{
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct aaci_runtime *aacirun = runtime->private_data;

	aacirun->start	= (void *)runtime->dma_area;
	aacirun->end	= aacirun->start + runtime->dma_bytes;
	aacirun->ptr	= aacirun->start;
	aacirun->period	=
	aacirun->bytes	= frames_to_bytes(runtime, runtime->period_size);

	return 0;
}