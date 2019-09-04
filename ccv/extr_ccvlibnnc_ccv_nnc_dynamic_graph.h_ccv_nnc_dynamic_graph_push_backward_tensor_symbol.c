#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  d; } ;
typedef  TYPE_1__ ccv_nnc_tensor_symbol_t ;
typedef  int /*<<< orphan*/  ccv_nnc_tensor_param_t ;
struct TYPE_6__ {int /*<<< orphan*/  type; int /*<<< orphan*/  d; } ;
typedef  TYPE_2__ ccv_nnc_tape_symbol_t ;
typedef  int /*<<< orphan*/  ccv_array_t ;

/* Variables and functions */
 int /*<<< orphan*/  CCV_NNC_SYMBOL_TENSOR ; 
 int /*<<< orphan*/  ccv_array_push (int /*<<< orphan*/ * const,TYPE_2__*) ; 

__attribute__((used)) static inline void ccv_nnc_dynamic_graph_push_backward_tensor_symbol(void* context, const ccv_nnc_tensor_symbol_t symbol, const ccv_nnc_tensor_param_t info, const char* const name)
{
	ccv_array_t* const stack = (ccv_array_t*)context;
	ccv_nnc_tape_symbol_t tape_symbol = {
		.d = symbol.d,
		.type = CCV_NNC_SYMBOL_TENSOR,
	};
	ccv_array_push(stack, &tape_symbol);
}