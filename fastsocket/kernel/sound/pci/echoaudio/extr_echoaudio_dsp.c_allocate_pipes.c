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
typedef  int u32 ;
struct echoaudio {int pipe_alloc_mask; int pipe_cyclic_mask; TYPE_1__* comm_page; scalar_t__ bad_board; } ;
struct audiopipe {int index; int interleave; scalar_t__* dma_counter; int /*<<< orphan*/  state; } ;
struct TYPE_2__ {scalar_t__* position; } ;

/* Variables and functions */
 int /*<<< orphan*/  DE_ACT (char*) ; 
 int EAGAIN ; 
 int EIO ; 
 int /*<<< orphan*/  PIPE_STATE_STOPPED ; 

__attribute__((used)) static int allocate_pipes(struct echoaudio *chip, struct audiopipe *pipe,
			  int pipe_index, int interleave)
{
	int i;
	u32 channel_mask;
	char is_cyclic;

	DE_ACT(("allocate_pipes: ch=%d int=%d\n", pipe_index, interleave));

	if (chip->bad_board)
		return -EIO;

	is_cyclic = 1;	/* This driver uses cyclic buffers only */

	for (channel_mask = i = 0; i < interleave; i++)
		channel_mask |= 1 << (pipe_index + i);
	if (chip->pipe_alloc_mask & channel_mask) {
		DE_ACT(("allocate_pipes: channel already open\n"));
		return -EAGAIN;
	}

	chip->comm_page->position[pipe_index] = 0;
	chip->pipe_alloc_mask |= channel_mask;
	if (is_cyclic)
		chip->pipe_cyclic_mask |= channel_mask;
	pipe->index = pipe_index;
	pipe->interleave = interleave;
	pipe->state = PIPE_STATE_STOPPED;

	/* The counter register is where the DSP writes the 32 bit DMA
	position for a pipe.  The DSP is constantly updating this value as
	it moves data. The DMA counter is in units of bytes, not samples. */
	pipe->dma_counter = &chip->comm_page->position[pipe_index];
	*pipe->dma_counter = 0;
	DE_ACT(("allocate_pipes: ok\n"));
	return pipe_index;
}