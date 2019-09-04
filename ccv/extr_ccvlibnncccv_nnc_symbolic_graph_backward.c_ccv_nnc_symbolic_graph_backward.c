#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_8__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
struct TYPE_19__ {int /*<<< orphan*/  d; TYPE_4__* const graph; } ;
typedef  TYPE_2__ ccv_nnc_tensor_symbol_t ;
struct TYPE_20__ {int /*<<< orphan*/  alias_ref; } ;
typedef  TYPE_3__ ccv_nnc_tensor_symbol_info_t ;
struct TYPE_21__ {TYPE_8__* tensor_symbol_info; TYPE_1__* exec_symbol_info; } ;
typedef  TYPE_4__ ccv_nnc_symbolic_graph_t ;
typedef  int /*<<< orphan*/  ccv_nnc_symbolic_graph_backward_prep_t ;
typedef  int /*<<< orphan*/  ccv_nnc_graph_exec_symbol_t ;
struct TYPE_22__ {int rnum; } ;
struct TYPE_18__ {int rnum; } ;

/* Variables and functions */
 int /*<<< orphan*/  _ccv_nnc_symbolic_graph_backward_gen (int /*<<< orphan*/ *,TYPE_2__ const* const,int const,TYPE_2__ const* const,int const,TYPE_4__* const,TYPE_4__* const) ; 
 int /*<<< orphan*/  _ccv_nnc_symbolic_graph_backward_prep (TYPE_4__* const,int /*<<< orphan*/  const* const,int const,int /*<<< orphan*/  const* const,int const) ; 
 int /*<<< orphan*/  _ccv_nnc_symbolic_graph_backward_prep_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _ccv_nnc_symbolic_graph_backward_prep_gen (int /*<<< orphan*/ *,TYPE_2__ const* const,int const,TYPE_2__ const* const,int const,int /*<<< orphan*/ ,int /*<<< orphan*/  const* const,int const,int /*<<< orphan*/  const* const,int const) ; 
 int /*<<< orphan*/  _ccv_nnc_symbolic_graph_backward_prep_prune_ops (int /*<<< orphan*/ *,TYPE_2__ const* const,int const,TYPE_2__ const* const,int const,int /*<<< orphan*/  const* const,int const,int /*<<< orphan*/  const* const,int const) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ ccv_array_get (TYPE_8__*,int /*<<< orphan*/ ) ; 

void ccv_nnc_symbolic_graph_backward(ccv_nnc_symbolic_graph_t* const graph, const ccv_nnc_tensor_symbol_t* const f_symbols, const int f_symbol_size, const ccv_nnc_tensor_symbol_t* const wrt_symbols, const int wrt_symbol_size, const ccv_nnc_graph_exec_symbol_t* const sources, const int source_size, const ccv_nnc_graph_exec_symbol_t* const destinations, const int destination_size)
{
	int i;
	// TODO: f symbols cannot be alias yet.
	for (i = 0; i < f_symbol_size; i++)
	{
		assert(f_symbols[i].graph == graph); // f symbol has to be in the current graph.
		assert(!((ccv_nnc_tensor_symbol_info_t*)ccv_array_get(graph->tensor_symbol_info, f_symbols[i].d))->alias_ref);
	}
	// TODO: wrt symbols cannot be alias yet.
	for (i = 0; i < wrt_symbol_size; i++)
	{
		assert(wrt_symbols[i].graph == graph);
		assert(!((ccv_nnc_tensor_symbol_info_t*)ccv_array_get(graph->tensor_symbol_info, wrt_symbols[i].d))->alias_ref);
	}
	const int exec_symbol_info_size = graph->exec_symbol_info->rnum;
	const int tensor_symbol_info_size = graph->tensor_symbol_info->rnum;
	assert(exec_symbol_info_size > 0);
	assert(tensor_symbol_info_size > 0);
	ccv_nnc_symbolic_graph_backward_prep_t backward_prep = _ccv_nnc_symbolic_graph_backward_prep(graph, sources, source_size, destinations, destination_size);
	_ccv_nnc_symbolic_graph_backward_prep_prune_ops(&backward_prep, f_symbols, f_symbol_size, wrt_symbols, wrt_symbol_size, sources, source_size, destinations, destination_size);
	_ccv_nnc_symbolic_graph_backward_prep_gen(&backward_prep, f_symbols, f_symbol_size, wrt_symbols, wrt_symbol_size, 0, sources, source_size, destinations, destination_size);
	_ccv_nnc_symbolic_graph_backward_gen(&backward_prep, f_symbols, f_symbol_size, wrt_symbols, wrt_symbol_size, graph, graph);
	_ccv_nnc_symbolic_graph_backward_prep_free(backward_prep);
}