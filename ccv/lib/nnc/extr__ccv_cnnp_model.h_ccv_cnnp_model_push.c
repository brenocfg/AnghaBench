#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ name; } ;
typedef  TYPE_1__ ccv_cnnp_model_t ;
struct TYPE_7__ {scalar_t__ it; scalar_t__ sequences; } ;
typedef  TYPE_2__ ccv_cnnp_model_sequence_t ;
struct TYPE_8__ {scalar_t__ name; int /*<<< orphan*/  type; int /*<<< orphan*/  sequence; } ;
typedef  TYPE_3__ ccv_cnnp_model_name_t ;

/* Variables and functions */
 int /*<<< orphan*/  CCV_CNNP_MODEL_NAME ; 
 int /*<<< orphan*/  CCV_CNNP_MODEL_SEQUENCE ; 
 scalar_t__ ccv_array_new (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ccv_array_push (scalar_t__,TYPE_3__*) ; 

__attribute__((used)) static inline void ccv_cnnp_model_push(const ccv_cnnp_model_t* const self, void* const context)
{
	ccv_cnnp_model_sequence_t* const model_sequence = (ccv_cnnp_model_sequence_t*)context;
	// Reset to 0.
	if (!model_sequence->sequences)
		model_sequence->sequences = ccv_array_new(sizeof(ccv_cnnp_model_name_t), 1, 0);
	ccv_cnnp_model_name_t name = {
		.type = CCV_CNNP_MODEL_SEQUENCE,
		.sequence = 0,
	};
	if (self->name)
	{
		name.type = CCV_CNNP_MODEL_NAME;
		name.name = self->name;
	}
	ccv_array_push(model_sequence->sequences, &name);
	model_sequence->it = 0;
}