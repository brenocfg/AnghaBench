#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {void* bytes; } ;
struct snd_pcm_substream {TYPE_3__ dma_buffer; TYPE_1__* runtime; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct snd_emu8k_pcm {TYPE_4__* block; scalar_t__ offset; void* allocated_bytes; TYPE_2__* emu; } ;
struct TYPE_9__ {int offset; } ;
struct TYPE_7__ {int /*<<< orphan*/  memhdr; } ;
struct TYPE_6__ {struct snd_emu8k_pcm* private_data; } ;

/* Variables and functions */
 scalar_t__ EMU8000_DRAM_OFFSET ; 
 int ENOMEM ; 
 int LOOP_BLANK_SIZE ; 
 void* params_buffer_bytes (struct snd_pcm_hw_params*) ; 
 TYPE_4__* snd_util_mem_alloc (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  snd_util_mem_free (int /*<<< orphan*/ ,TYPE_4__*) ; 

__attribute__((used)) static int emu8k_pcm_hw_params(struct snd_pcm_substream *subs,
			       struct snd_pcm_hw_params *hw_params)
{
	struct snd_emu8k_pcm *rec = subs->runtime->private_data;

	if (rec->block) {
		/* reallocation - release the old block */
		snd_util_mem_free(rec->emu->memhdr, rec->block);
		rec->block = NULL;
	}

	rec->allocated_bytes = params_buffer_bytes(hw_params) + LOOP_BLANK_SIZE * 4;
	rec->block = snd_util_mem_alloc(rec->emu->memhdr, rec->allocated_bytes);
	if (! rec->block)
		return -ENOMEM;
	rec->offset = EMU8000_DRAM_OFFSET + (rec->block->offset >> 1); /* in word */
	/* at least dma_bytes must be set for non-interleaved mode */
	subs->dma_buffer.bytes = params_buffer_bytes(hw_params);

	return 0;
}