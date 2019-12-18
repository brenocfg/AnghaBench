#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int assign_ref; int r_assign_ref; } ;
typedef  TYPE_2__ ccv_nnc_tensor_symbol_info_t ;
typedef  int /*<<< orphan*/  ccv_nnc_tensor_block_t ;
struct TYPE_8__ {TYPE_1__* tensor_symbol_info; } ;
typedef  TYPE_3__ ccv_nnc_symbolic_graph_t ;
struct TYPE_6__ {int rnum; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static void _ccv_nnc_fixup_assign_ref_after_unroll(const ccv_nnc_symbolic_graph_t* const symbolic_graph, const int unroll_count, const ccv_nnc_tensor_block_t* const tensor_blocks, const int* const dup_tensor_block_ref, ccv_nnc_tensor_symbol_info_t* const dup_tensor_symbol_info)
{
	int i;
	for (i = 0; i < symbolic_graph->tensor_symbol_info->rnum; i++) // symbolic graph is the old graph and tensor blocks is the old tensor blocks.
		// Now can assign them (The dup) as companion.
		// Get to the last one, which we will wrap over.
		if (dup_tensor_symbol_info[i].assign_ref)
		{
			dup_tensor_symbol_info[dup_tensor_symbol_info[i].assign_ref - 1].r_assign_ref = 0;
			dup_tensor_symbol_info[i].assign_ref = dup_tensor_block_ref[(dup_tensor_symbol_info[i].assign_ref - 1) * unroll_count + unroll_count - 1] + 1;
			assert(dup_tensor_symbol_info[i].assign_ref);
			dup_tensor_symbol_info[dup_tensor_symbol_info[i].assign_ref - 1].r_assign_ref = i + 1;
		}
}