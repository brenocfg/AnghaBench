#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ccv_cnnp_model_t ;
struct TYPE_9__ {float momentum; float epsilon; } ;
struct TYPE_10__ {TYPE_3__ bnorm; } ;
struct TYPE_8__ {scalar_t__ graph; void* d; } ;
struct TYPE_7__ {scalar_t__ graph; void* d; } ;
struct TYPE_12__ {int input_size; int output_size; int /*<<< orphan*/ * outputs; int /*<<< orphan*/ * isa; } ;
struct TYPE_11__ {TYPE_4__ params; TYPE_2__ bias; TYPE_1__ scale; TYPE_6__ super; int /*<<< orphan*/  output; } ;
typedef  TYPE_5__ ccv_cnnp_model_batch_norm_t ;

/* Variables and functions */
 void* CCV_NNC_NO_TENSOR_SYMBOL ; 
 scalar_t__ cccalloc (int,int) ; 
 int /*<<< orphan*/  ccv_cnnp_batch_norm_isa ; 
 int /*<<< orphan*/  ccv_cnnp_model_copy_name (TYPE_6__*,char const* const) ; 

ccv_cnnp_model_t* ccv_cnnp_batch_norm(const float momentum, const float epsilon, const char* const name)
{
	ccv_cnnp_model_batch_norm_t* const model_batch_norm = (ccv_cnnp_model_batch_norm_t*)cccalloc(1, sizeof(ccv_cnnp_model_batch_norm_t));
	model_batch_norm->super.isa = &ccv_cnnp_batch_norm_isa;
	model_batch_norm->super.input_size = 1;
	model_batch_norm->super.outputs = &model_batch_norm->output;
	model_batch_norm->super.output_size = 1;
	ccv_cnnp_model_copy_name(&model_batch_norm->super, name);
	model_batch_norm->scale.d = CCV_NNC_NO_TENSOR_SYMBOL;
	model_batch_norm->scale.graph = 0;
	model_batch_norm->bias.d = CCV_NNC_NO_TENSOR_SYMBOL;
	model_batch_norm->bias.graph = 0;
	model_batch_norm->params.bnorm.momentum = momentum;
	model_batch_norm->params.bnorm.epsilon = epsilon;
	return (ccv_cnnp_model_t*)model_batch_norm;
}