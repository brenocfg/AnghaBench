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
typedef  int /*<<< orphan*/  ccv_cnnp_model_t ;
struct TYPE_5__ {scalar_t__ graph; } ;
struct TYPE_4__ {TYPE_2__ scale; TYPE_2__ bias; } ;
typedef  TYPE_1__ ccv_cnnp_model_batch_norm_t ;
typedef  int /*<<< orphan*/  (* ccv_cnnp_add_to_array_f ) (void* const,TYPE_2__) ;

/* Variables and functions */

__attribute__((used)) static void _ccv_cnnp_layer_norm_add_to_trainable(ccv_cnnp_model_t* const super, const ccv_cnnp_add_to_array_f add_to_array, void* const trainables)
{
	ccv_cnnp_model_batch_norm_t* const self = (ccv_cnnp_model_batch_norm_t*)super;
	if (self->bias.graph)
		add_to_array(trainables, self->bias);
	if (self->scale.graph)
		add_to_array(trainables, self->scale);
}