#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ccv_cnnp_model_t ;
struct TYPE_4__ {TYPE_3__* sequences; } ;
typedef  TYPE_1__ ccv_cnnp_model_sequence_t ;
struct TYPE_5__ {scalar_t__ type; int /*<<< orphan*/  sequence; } ;
typedef  TYPE_2__ ccv_cnnp_model_name_t ;
struct TYPE_6__ {scalar_t__ rnum; } ;

/* Variables and functions */
 scalar_t__ CCV_CNNP_MODEL_SEQUENCE ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ ccv_array_get (TYPE_3__*,scalar_t__) ; 

__attribute__((used)) static inline void ccv_cnnp_model_pop(const ccv_cnnp_model_t* const self, void* const context)
{
	ccv_cnnp_model_sequence_t* const model_sequence = (ccv_cnnp_model_sequence_t*)context;
	--model_sequence->sequences->rnum;
	assert(model_sequence->sequences->rnum >= 0);
	if (model_sequence->sequences->rnum > 0)
	{
		ccv_cnnp_model_name_t* const name = (ccv_cnnp_model_name_t*)ccv_array_get(model_sequence->sequences, model_sequence->sequences->rnum - 1);
		if (name->type == CCV_CNNP_MODEL_SEQUENCE)
			++name->sequence;
	}
}