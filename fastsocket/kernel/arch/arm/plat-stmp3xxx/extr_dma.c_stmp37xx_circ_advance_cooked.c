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
struct stmp37xx_circ_dma_chain {unsigned int active_count; unsigned int active_index; unsigned int total_count; unsigned int cooked_count; int /*<<< orphan*/  bus; int /*<<< orphan*/  channel; } ;

/* Variables and functions */
 int /*<<< orphan*/  STMP3XXX_DMA (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int stmp3xxx_dma_read_semaphore (int /*<<< orphan*/ ) ; 

unsigned stmp37xx_circ_advance_cooked(struct stmp37xx_circ_dma_chain *chain)
{
	unsigned cooked;

	cooked = chain->active_count -
	  stmp3xxx_dma_read_semaphore(STMP3XXX_DMA(chain->channel, chain->bus));

	chain->active_count -= cooked;
	chain->active_index += cooked;
	chain->active_index %= chain->total_count;

	chain->cooked_count += cooked;

	return cooked;
}