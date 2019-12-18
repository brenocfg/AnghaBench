#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_7__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ d; TYPE_3__* graph; } ;
typedef  TYPE_1__ ccv_nnc_tensor_symbol_t ;
struct TYPE_9__ {scalar_t__ pair_ref; } ;
typedef  TYPE_2__ ccv_nnc_tensor_symbol_info_t ;
struct TYPE_10__ {TYPE_7__* tensor_symbol_info; struct TYPE_10__* pair; } ;
typedef  TYPE_3__ ccv_nnc_symbolic_graph_t ;
struct TYPE_11__ {scalar_t__ rnum; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ ccv_array_get (TYPE_7__*,scalar_t__) ; 

void ccv_nnc_tensor_symbol_pair_with(ccv_nnc_symbolic_graph_t* const graph, const ccv_nnc_tensor_symbol_t tensor_symbol, const ccv_nnc_tensor_symbol_t pair_tensor_symbol)
{
	assert(tensor_symbol.graph == graph);
	assert(tensor_symbol.d >= 0);
	assert(tensor_symbol.d < graph->tensor_symbol_info->rnum);
	assert(pair_tensor_symbol.graph == graph->pair);
	assert(pair_tensor_symbol.d >= 0);
	assert(pair_tensor_symbol.d < graph->pair->tensor_symbol_info->rnum);
	ccv_nnc_tensor_symbol_info_t* const tensor_info = (ccv_nnc_tensor_symbol_info_t*)ccv_array_get(graph->tensor_symbol_info, tensor_symbol.d);
	tensor_info->pair_ref = pair_tensor_symbol.d + 1;
}