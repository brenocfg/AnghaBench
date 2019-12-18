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
struct stmp37xx_circ_dma_chain {unsigned int cooked_count; int /*<<< orphan*/  free_count; int /*<<< orphan*/  total_count; int /*<<< orphan*/  cooked_index; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 

void stmp37xx_circ_advance_free(struct stmp37xx_circ_dma_chain *chain,
		unsigned count)
{
	BUG_ON(chain->cooked_count < count);

	chain->cooked_count -= count;
	chain->cooked_index += count;
	chain->cooked_index %= chain->total_count;
	chain->free_count += count;
}