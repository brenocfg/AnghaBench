#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ccv_nnc_tensor_symbol_t ;
typedef  int /*<<< orphan*/  ccv_nnc_tensor_param_t ;
struct TYPE_3__ {int /*<<< orphan*/  const tensor; int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ ccv_cnnp_rewind_symbol_t ;
typedef  int /*<<< orphan*/  ccv_array_t ;

/* Variables and functions */
 int /*<<< orphan*/  CCV_CNNP_REWIND_TENSOR ; 
 int /*<<< orphan*/  ccv_array_push (int /*<<< orphan*/ * const,TYPE_1__ const*) ; 

__attribute__((used)) static void _ccv_cnnp_model_tensor_symbol_new_hook(void* context, const ccv_nnc_tensor_symbol_t symbol, const ccv_nnc_tensor_param_t info, const char* const name)
{
	const ccv_cnnp_rewind_symbol_t rewind_symbol = {
		.type = CCV_CNNP_REWIND_TENSOR,
		.tensor = symbol
	};
	ccv_array_t* const rewind_symbols = (ccv_array_t*)context;
	ccv_array_push(rewind_symbols, &rewind_symbol);
}