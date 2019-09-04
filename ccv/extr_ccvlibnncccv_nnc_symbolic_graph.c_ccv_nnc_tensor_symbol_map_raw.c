#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ d; TYPE_2__* graph; } ;
typedef  TYPE_1__ ccv_nnc_tensor_symbol_t ;
struct TYPE_8__ {struct TYPE_8__* p; } ;
typedef  TYPE_2__ ccv_nnc_symbolic_graph_t ;

/* Variables and functions */
 int CCV_NNC_ENCODE_WHILE_COUNT_SYMBOL (int) ; 
 scalar_t__ CCV_NNC_NO_TENSOR_SYMBOL ; 
 int /*<<< orphan*/  MAP_TENSOR_USE_AS_INPUT ; 
 int _ccv_nnc_symbolic_graph_map_tensor_symbol (TYPE_2__* const,TYPE_1__ const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 

int ccv_nnc_tensor_symbol_map_raw(ccv_nnc_symbolic_graph_t* const graph, const ccv_nnc_tensor_symbol_t symbol)
{
	if (symbol.d >= 0)
		return symbol.graph != graph ? _ccv_nnc_symbolic_graph_map_tensor_symbol(graph, symbol, MAP_TENSOR_USE_AS_INPUT) : symbol.d;
	if (symbol.graph == graph || symbol.d == CCV_NNC_NO_TENSOR_SYMBOL)
		return symbol.d;
	ccv_nnc_symbolic_graph_t* curr_graph = graph;
	int d;
	for (d = 0; curr_graph && curr_graph != symbol.graph; d++)
		curr_graph = curr_graph->p;
	assert(curr_graph == symbol.graph);
	return CCV_NNC_ENCODE_WHILE_COUNT_SYMBOL(d);
}