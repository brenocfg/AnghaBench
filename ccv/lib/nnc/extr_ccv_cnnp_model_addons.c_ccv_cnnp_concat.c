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
struct TYPE_4__ {int input_size; int output_size; int /*<<< orphan*/ * outputs; int /*<<< orphan*/ * isa; } ;
struct TYPE_3__ {TYPE_2__ super; int /*<<< orphan*/  output; } ;
typedef  TYPE_1__ ccv_cnnp_model_concat_t ;

/* Variables and functions */
 scalar_t__ cccalloc (int,int) ; 
 int /*<<< orphan*/  ccv_cnnp_concat_isa ; 
 int /*<<< orphan*/  ccv_cnnp_model_copy_name (TYPE_2__*,char const* const) ; 

ccv_cnnp_model_t* ccv_cnnp_concat(const char* const name)
{
	ccv_cnnp_model_concat_t* const model_concat = (ccv_cnnp_model_concat_t*)cccalloc(1, sizeof(ccv_cnnp_model_concat_t));
	model_concat->super.isa = &ccv_cnnp_concat_isa;
	model_concat->super.input_size = 1;
	model_concat->super.outputs = &model_concat->output;
	model_concat->super.output_size = 1;
	ccv_cnnp_model_copy_name(&model_concat->super, name);
	return (ccv_cnnp_model_t*)model_concat;
}