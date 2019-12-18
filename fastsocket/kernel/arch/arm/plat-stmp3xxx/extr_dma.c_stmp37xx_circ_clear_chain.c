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
struct stmp37xx_circ_dma_chain {scalar_t__ cooked_count; scalar_t__ active_count; int /*<<< orphan*/  total_count; int /*<<< orphan*/  free_count; scalar_t__ cooked_index; scalar_t__ active_index; scalar_t__ free_index; int /*<<< orphan*/  bus; int /*<<< orphan*/  channel; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STMP3XXX_DMA (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stmp3xxx_dma_running (int /*<<< orphan*/ ) ; 

void stmp37xx_circ_clear_chain(struct stmp37xx_circ_dma_chain *chain)
{
	BUG_ON(stmp3xxx_dma_running(STMP3XXX_DMA(chain->channel, chain->bus)));
	chain->free_index = 0;
	chain->active_index = 0;
	chain->cooked_index = 0;
	chain->free_count = chain->total_count;
	chain->active_count = 0;
	chain->cooked_count = 0;
}