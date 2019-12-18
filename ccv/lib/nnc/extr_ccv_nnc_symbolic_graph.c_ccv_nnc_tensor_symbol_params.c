#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ d; TYPE_3__ const* const graph; } ;
typedef  TYPE_1__ ccv_nnc_tensor_symbol_t ;
struct TYPE_8__ {int /*<<< orphan*/  info; } ;
typedef  TYPE_2__ ccv_nnc_tensor_symbol_info_t ;
typedef  int /*<<< orphan*/  ccv_nnc_tensor_param_t ;
struct TYPE_9__ {TYPE_6__* tensor_symbol_info; } ;
typedef  TYPE_3__ ccv_nnc_symbolic_graph_t ;
struct TYPE_10__ {scalar_t__ rnum; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ ccv_array_get (TYPE_6__*,scalar_t__) ; 

ccv_nnc_tensor_param_t ccv_nnc_tensor_symbol_params(const ccv_nnc_symbolic_graph_t* const graph, const ccv_nnc_tensor_symbol_t tensor)
{
	assert(graph == tensor.graph);
	assert(tensor.d < graph->tensor_symbol_info->rnum);
	ccv_nnc_tensor_symbol_info_t* const symbol_info = (ccv_nnc_tensor_symbol_info_t*)ccv_array_get(graph->tensor_symbol_info, tensor.d);
	return symbol_info->info;
}