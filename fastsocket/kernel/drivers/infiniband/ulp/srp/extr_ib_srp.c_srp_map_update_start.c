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
struct srp_map_state {int unmapped_index; int /*<<< orphan*/  unmapped_addr; struct scatterlist* unmapped_sg; } ;
struct scatterlist {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */

__attribute__((used)) static void srp_map_update_start(struct srp_map_state *state,
				 struct scatterlist *sg, int sg_index,
				 dma_addr_t dma_addr)
{
	state->unmapped_sg = sg;
	state->unmapped_index = sg_index;
	state->unmapped_addr = dma_addr;
}