#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ccv_nnc_tensor_t ;
struct TYPE_5__ {TYPE_1__* tensor_arena; int /*<<< orphan*/  while_count_tensor; struct TYPE_5__* p; } ;
typedef  TYPE_2__ ccv_nnc_symbolic_graph_prep_t ;
struct TYPE_4__ {int /*<<< orphan*/  tensor_metadata; int /*<<< orphan*/ ** vt_tensors; } ;

/* Variables and functions */
 int CCV_NNC_DECODE_WHILE_COUNT_SYMBOL (int const) ; 
 int /*<<< orphan*/  CCV_NNC_IS_WHILE_COUNT_TENSOR_SYMBOL (int const) ; 
 int const CCV_NNC_NO_TENSOR_SYMBOL ; 
 scalar_t__ _ccv_nnc_tensor_metadata_get (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ccv_nnc_tensor_t* _ccv_nnc_tensor_from_graph_prep(const ccv_nnc_symbolic_graph_prep_t* const graph_prep, const int symbol)
{
	if (symbol >= 0)
		return graph_prep->tensor_arena->vt_tensors[symbol];
	if (symbol == CCV_NNC_NO_TENSOR_SYMBOL)
		return 0;
	assert(CCV_NNC_IS_WHILE_COUNT_TENSOR_SYMBOL(symbol));
	const ccv_nnc_symbolic_graph_prep_t* prep = graph_prep;
	int i;
	const int d = CCV_NNC_DECODE_WHILE_COUNT_SYMBOL(symbol);
	for (i = 0; i < d; i++)
		prep = prep->p;
	assert(prep->while_count_tensor);
	return (ccv_nnc_tensor_t*)_ccv_nnc_tensor_metadata_get(prep->tensor_arena->tensor_metadata, (0 << 1) + 1);
}