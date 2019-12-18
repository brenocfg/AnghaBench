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
struct snd_pcm_runtime {scalar_t__ buffer_size; struct atmel_runtime_data* private_data; } ;
struct atmel_runtime_data {scalar_t__ dma_buffer; struct atmel_pcm_dma_params* params; } ;
struct atmel_pcm_dma_params {TYPE_1__* pdc; TYPE_2__* ssc; } ;
typedef  scalar_t__ snd_pcm_uframes_t ;
typedef  scalar_t__ dma_addr_t ;
struct TYPE_4__ {int /*<<< orphan*/  regs; } ;
struct TYPE_3__ {int /*<<< orphan*/  xpr; } ;

/* Variables and functions */
 scalar_t__ bytes_to_frames (struct snd_pcm_runtime*,scalar_t__) ; 
 scalar_t__ ssc_readx (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static snd_pcm_uframes_t atmel_pcm_pointer(
	struct snd_pcm_substream *substream)
{
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct atmel_runtime_data *prtd = runtime->private_data;
	struct atmel_pcm_dma_params *params = prtd->params;
	dma_addr_t ptr;
	snd_pcm_uframes_t x;

	ptr = (dma_addr_t) ssc_readx(params->ssc->regs, params->pdc->xpr);
	x = bytes_to_frames(runtime, ptr - prtd->dma_buffer);

	if (x == runtime->buffer_size)
		x = 0;

	return x;
}