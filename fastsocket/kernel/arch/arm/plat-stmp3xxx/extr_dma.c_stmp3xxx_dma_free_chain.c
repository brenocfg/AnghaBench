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
struct stmp37xx_circ_dma_chain {int total_count; int /*<<< orphan*/ * chain; int /*<<< orphan*/  bus; int /*<<< orphan*/  channel; } ;

/* Variables and functions */
 int /*<<< orphan*/  STMP3XXX_DMA (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stmp3xxx_dma_free_command (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void stmp3xxx_dma_free_chain(struct stmp37xx_circ_dma_chain *chain)
{
	int i;

	for (i = 0; i < chain->total_count; i++)
		stmp3xxx_dma_free_command(
			STMP3XXX_DMA(chain->channel, chain->bus),
			&chain->chain[i]);
}