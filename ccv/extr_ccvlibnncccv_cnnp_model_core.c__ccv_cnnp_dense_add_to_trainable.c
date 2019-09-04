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
typedef  int /*<<< orphan*/  ccv_cnnp_model_t ;
struct TYPE_4__ {scalar_t__ graph; } ;
struct TYPE_3__ {TYPE_2__ scale; TYPE_2__ bias; TYPE_2__ weights; } ;
typedef  TYPE_1__ ccv_cnnp_model_dense_t ;
typedef  int /*<<< orphan*/  ccv_array_t ;

/* Variables and functions */
 int /*<<< orphan*/  ccv_array_push (int /*<<< orphan*/ * const,TYPE_2__*) ; 

__attribute__((used)) static void _ccv_cnnp_dense_add_to_trainable(ccv_cnnp_model_t* const super, ccv_array_t* const trainables)
{
	ccv_cnnp_model_dense_t* const self = (ccv_cnnp_model_dense_t*)super;
	ccv_array_push(trainables, &self->weights);
	if (self->bias.graph)
		ccv_array_push(trainables, &self->bias);
	if (self->scale.graph)
		ccv_array_push(trainables, &self->scale);
}