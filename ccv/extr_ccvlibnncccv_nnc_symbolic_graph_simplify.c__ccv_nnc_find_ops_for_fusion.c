#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int uint32_t ;
struct TYPE_8__ {scalar_t__* ops_seq; int ops_seq_size; } ;
typedef  TYPE_2__ ccv_nnc_ops_fusion_t ;
struct TYPE_7__ {scalar_t__ cmd; } ;
struct TYPE_9__ {TYPE_4__* outgoings; TYPE_1__ cmd; } ;
typedef  TYPE_3__ ccv_nnc_graph_exec_symbol_info_t ;
struct TYPE_10__ {int rnum; } ;

/* Variables and functions */
 scalar_t__ ccv_array_get (TYPE_4__*,int) ; 

__attribute__((used)) static int _ccv_nnc_find_ops_for_fusion(const ccv_nnc_ops_fusion_t* const fusion, const int ops_idx, const ccv_nnc_graph_exec_symbol_info_t* const exec_symbol_info, const uint32_t* const exec_dead, const int exec_idx, int* const fusing_exec_symbols)
{
	if (exec_dead[exec_idx >> 5] & (1u << (exec_idx & 0x1f)))
		return 0;
	const ccv_nnc_graph_exec_symbol_info_t* const node = exec_symbol_info + exec_idx;
	// Doesn't match the ops_seq, return 0.
	if (fusion->ops_seq[ops_idx] != node->cmd.cmd)
		return 0;
	fusing_exec_symbols[ops_idx] = exec_idx;
	// If already reached the end, we are good.
	if (ops_idx == fusion->ops_seq_size - 1)
		return 1;
	// Otherwise, we need to go on, but don't have any to follow-up.
	if (!node->outgoings || !node->outgoings->rnum)
		return 0;
	int i;
	for (i = 0; i < node->outgoings->rnum; i++)
		if (_ccv_nnc_find_ops_for_fusion(fusion, ops_idx + 1, exec_symbol_info, exec_dead, *(int*)ccv_array_get(node->outgoings, i), fusing_exec_symbols))
			return 1;
	return 0;
}