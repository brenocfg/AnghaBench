#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ccv_cnnp_model_t ;
struct TYPE_2__ {scalar_t__ retainables; scalar_t__ zero_inits; } ;
typedef  TYPE_1__ ccv_cnnp_model_batch_norm_t ;

/* Variables and functions */
 int /*<<< orphan*/  ccv_array_free (scalar_t__) ; 

__attribute__((used)) static void _ccv_cnnp_batch_norm_deinit(ccv_cnnp_model_t* const super)
{
	ccv_cnnp_model_batch_norm_t* const self = (ccv_cnnp_model_batch_norm_t*)super;
	if (self->zero_inits)
		ccv_array_free(self->zero_inits);
	if (self->retainables)
		ccv_array_free(self->retainables);
}