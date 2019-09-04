#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ccv_nnc_tensor_t ;
struct TYPE_5__ {scalar_t__ d; } ;
typedef  TYPE_1__ ccv_nnc_tensor_symbol_t ;
typedef  int /*<<< orphan*/  ccv_nnc_symbolic_graph_t ;

/* Variables and functions */
 scalar_t__ CCV_NNC_NO_TENSOR_SYMBOL ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  ccv_nnc_tensor_free (int /*<<< orphan*/ *) ; 
 TYPE_1__ ccv_nnc_tensor_symbol_copy (int /*<<< orphan*/  const* const,TYPE_1__ const,int) ; 

__attribute__((used)) static void _ccv_cnnp_model_remove_nocopies(const ccv_nnc_symbolic_graph_t* const graph, const ccv_nnc_tensor_symbol_t* const tensor_symbols, ccv_nnc_tensor_t** const tensors, const int tensor_size, const int parallel_count)
{
	assert(parallel_count > 0);
	int i, j;
	for (i = 0; i < tensor_size; i++)
	{
		const ccv_nnc_tensor_symbol_t tensor_symbol = tensor_symbols[i];
		for (j = 1; j < parallel_count; j++)
		{
			const ccv_nnc_tensor_symbol_t copy = ccv_nnc_tensor_symbol_copy(graph, tensor_symbol, j);
			ccv_nnc_tensor_t* copy_tensor = tensors[i + j * tensor_size];
			if (copy_tensor && copy.d == CCV_NNC_NO_TENSOR_SYMBOL)
			{ // We shouldn't allocate this, free it up.
				ccv_nnc_tensor_free(tensors[i + j * tensor_size]);
				tensors[i + j * tensor_size] = 0;
			}
		}
	}
}