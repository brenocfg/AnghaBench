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
typedef  int /*<<< orphan*/  ccv_nnc_tensor_symbol_t ;
typedef  int /*<<< orphan*/  ccv_nnc_symbolic_graph_t ;
typedef  int /*<<< orphan*/  ccv_nnc_symbolic_graph_simplify_t ;
typedef  int /*<<< orphan*/  ccv_nnc_graph_exec_symbol_t ;

/* Variables and functions */
#define  CCV_NNC_SIMPLIFY_COMMON_SUBEXPRESSION_ELIMINATION 131 
#define  CCV_NNC_SIMPLIFY_DATA_TRANSFER_OPT 130 
#define  CCV_NNC_SIMPLIFY_GRAPH_PRUNING 129 
#define  CCV_NNC_SIMPLIFY_OPS_FUSION 128 
 int /*<<< orphan*/  _ccv_nnc_symbolic_graph_common_subexpression_elimination (int /*<<< orphan*/ * const,int /*<<< orphan*/  const* const,int const) ; 
 int /*<<< orphan*/  _ccv_nnc_symbolic_graph_data_transfer_opt (int /*<<< orphan*/ * const,int /*<<< orphan*/  const* const,int const) ; 
 int /*<<< orphan*/  _ccv_nnc_symbolic_graph_ops_fusion (int /*<<< orphan*/ * const,int /*<<< orphan*/  const* const,int const) ; 
 int /*<<< orphan*/  _ccv_nnc_symbolic_graph_pruning (int /*<<< orphan*/ * const,int /*<<< orphan*/  const* const,int const) ; 
 int /*<<< orphan*/  _ccv_nnc_symbolic_graph_simplify_apply (int /*<<< orphan*/ * const) ; 
 int /*<<< orphan*/  _ccv_nnc_symbolic_graph_simplify_free (int /*<<< orphan*/ * const) ; 
 int /*<<< orphan*/ * _ccv_nnc_symbolic_graph_simplify_new (int /*<<< orphan*/ * const,int /*<<< orphan*/  const* const,int const,int /*<<< orphan*/  const* const,int const) ; 

void ccv_nnc_symbolic_graph_simplify(ccv_nnc_symbolic_graph_t* const graph, const int* const passes, const int pass_size, const ccv_nnc_tensor_symbol_t* const outputs, const int output_size, const ccv_nnc_graph_exec_symbol_t* const sources, const int source_size, const ccv_nnc_graph_exec_symbol_t* const destinations, const int destination_size)
{
	ccv_nnc_symbolic_graph_simplify_t* const simplify = _ccv_nnc_symbolic_graph_simplify_new(graph, sources, source_size, destinations, destination_size);
	int i;
	for (i = 0; i < pass_size; i++)
		switch (passes[i])
		{
			case CCV_NNC_SIMPLIFY_COMMON_SUBEXPRESSION_ELIMINATION:
				_ccv_nnc_symbolic_graph_common_subexpression_elimination(simplify, outputs, output_size);
				break;
			case CCV_NNC_SIMPLIFY_DATA_TRANSFER_OPT:
				_ccv_nnc_symbolic_graph_data_transfer_opt(simplify, outputs, output_size);
				break;
			case CCV_NNC_SIMPLIFY_GRAPH_PRUNING:
				_ccv_nnc_symbolic_graph_pruning(simplify, outputs, output_size);
				break;
			case CCV_NNC_SIMPLIFY_OPS_FUSION:
				_ccv_nnc_symbolic_graph_ops_fusion(simplify, outputs, output_size);
				break;
		}
	_ccv_nnc_symbolic_graph_simplify_apply(simplify);
	_ccv_nnc_symbolic_graph_simplify_free(simplify);
}