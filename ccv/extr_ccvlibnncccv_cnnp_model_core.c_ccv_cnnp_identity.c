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
typedef  int /*<<< orphan*/  ccv_cnnp_param_t ;
typedef  int /*<<< orphan*/  ccv_cnnp_model_t ;
struct TYPE_4__ {scalar_t__ graph; int /*<<< orphan*/  d; } ;
struct TYPE_5__ {int input_size; int output_size; int /*<<< orphan*/ * outputs; int /*<<< orphan*/ * isa; } ;
struct TYPE_6__ {int /*<<< orphan*/  params; TYPE_1__ bias; TYPE_2__ super; int /*<<< orphan*/  output; } ;
typedef  TYPE_3__ ccv_cnnp_model_identity_t ;

/* Variables and functions */
 int /*<<< orphan*/  CCV_NNC_NO_TENSOR_SYMBOL ; 
 scalar_t__ cccalloc (int,int) ; 
 int /*<<< orphan*/  ccv_cnnp_identity_isa ; 

ccv_cnnp_model_t* ccv_cnnp_identity(const ccv_cnnp_param_t params)
{
	ccv_cnnp_model_identity_t* const model_identity = (ccv_cnnp_model_identity_t*)cccalloc(1, sizeof(ccv_cnnp_model_identity_t));
	model_identity->super.isa = &ccv_cnnp_identity_isa;
	model_identity->super.input_size = 1;
	model_identity->super.outputs = &model_identity->output;
	model_identity->super.output_size = 1;
	model_identity->bias.d = CCV_NNC_NO_TENSOR_SYMBOL;
	model_identity->bias.graph = 0;
	model_identity->params = params;
	return (ccv_cnnp_model_t*)model_identity;
}