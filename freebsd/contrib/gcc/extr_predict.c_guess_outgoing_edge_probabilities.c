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
typedef  int /*<<< orphan*/  basic_block ;

/* Variables and functions */
 int /*<<< orphan*/  BB_END (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bb_estimate_probability_locally (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  combine_predictions_for_insn (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
guess_outgoing_edge_probabilities (basic_block bb)
{
  bb_estimate_probability_locally (bb);
  combine_predictions_for_insn (BB_END (bb), bb);
}