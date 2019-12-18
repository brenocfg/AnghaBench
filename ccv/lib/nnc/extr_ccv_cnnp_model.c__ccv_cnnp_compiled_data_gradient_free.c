#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ from_ops; } ;
struct TYPE_5__ {scalar_t__ tos; } ;
struct TYPE_7__ {TYPE_2__ backward; TYPE_1__ evaluate; scalar_t__ saved_aux; scalar_t__ update_nodes; scalar_t__ updated_trainables; scalar_t__ gradients; } ;
typedef  TYPE_3__ ccv_cnnp_compiled_data_t ;

/* Variables and functions */
 int /*<<< orphan*/  ccfree (scalar_t__) ; 

__attribute__((used)) static void _ccv_cnnp_compiled_data_gradient_free(ccv_cnnp_compiled_data_t* const compiled_data)
{
	if (compiled_data->gradients)
		ccfree(compiled_data->gradients);
	compiled_data->gradients = 0;
	if (compiled_data->updated_trainables)
		ccfree(compiled_data->updated_trainables);
	compiled_data->updated_trainables = 0;
	compiled_data->update_nodes = 0;
	compiled_data->saved_aux = 0;
	if (compiled_data->evaluate.tos)
		ccfree(compiled_data->evaluate.tos);
	compiled_data->evaluate.tos = 0;
	if (compiled_data->backward.from_ops)
		ccfree(compiled_data->backward.from_ops);
	compiled_data->backward.from_ops = 0;
}