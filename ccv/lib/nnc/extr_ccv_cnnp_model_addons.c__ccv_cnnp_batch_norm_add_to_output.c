#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ccv_nnc_tensor_symbol_t ;
typedef  int /*<<< orphan*/  ccv_cnnp_model_t ;
struct TYPE_3__ {TYPE_2__* retainables; } ;
typedef  TYPE_1__ ccv_cnnp_model_batch_norm_t ;
typedef  int /*<<< orphan*/  (* ccv_cnnp_add_to_array_f ) (void* const,int /*<<< orphan*/  const) ;
struct TYPE_4__ {int rnum; } ;

/* Variables and functions */
 scalar_t__ ccv_array_get (TYPE_2__*,int) ; 

__attribute__((used)) static void _ccv_cnnp_batch_norm_add_to_output(ccv_cnnp_model_t* const super, const ccv_cnnp_add_to_array_f add_to_array, void* const outputs)
{
	ccv_cnnp_model_batch_norm_t* const self = (ccv_cnnp_model_batch_norm_t*)super;
	int i;
	if (self->retainables)
		for (i = 0; i < self->retainables->rnum; i++)
		{
			const ccv_nnc_tensor_symbol_t symbol = *(ccv_nnc_tensor_symbol_t*)ccv_array_get(self->retainables, i);
			add_to_array(outputs, symbol);
		}
}