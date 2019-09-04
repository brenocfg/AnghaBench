#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct ccv_cnnp_model_io_s {int dummy; } ;
typedef  int /*<<< orphan*/  ccv_nnc_tensor_symbol_t ;
struct TYPE_9__ {int output_size; void* io; } ;
typedef  TYPE_1__ ccv_cnnp_model_t ;
typedef  TYPE_2__* ccv_cnnp_model_io_t ;
struct TYPE_10__ {void* outgoings; void* incomings; int /*<<< orphan*/ * outputs; TYPE_1__* model; scalar_t__ visit; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 TYPE_2__* ccmalloc (int) ; 
 int /*<<< orphan*/  ccv_array_get (void*,int /*<<< orphan*/ ) ; 
 void* ccv_array_new (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ccv_array_push (void*,TYPE_2__**) ; 
 int /*<<< orphan*/  ccv_array_resize (void*,int const) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,TYPE_2__* const* const,int) ; 

ccv_cnnp_model_io_t ccv_cnnp_model_apply(ccv_cnnp_model_t* const model, const ccv_cnnp_model_io_t* const inputs, const int input_size)
{
	assert(input_size > 0);
	if (!model->io)
		model->io = ccv_array_new(sizeof(ccv_cnnp_model_io_t), 1, 0);
	ccv_cnnp_model_io_t model_io = ccmalloc(sizeof(struct ccv_cnnp_model_io_s) + sizeof(ccv_nnc_tensor_symbol_t) * model->output_size);
	model_io->visit = 0;
	model_io->model = model;
	model_io->incomings = ccv_array_new(sizeof(ccv_cnnp_model_io_t), 1, 0);
	model_io->outgoings = 0;
	model_io->outputs = (ccv_nnc_tensor_symbol_t*)(model_io + 1);
	ccv_array_push(model->io, &model_io);
	int i;
	ccv_array_resize(model_io->incomings, input_size);
	memcpy(ccv_array_get(model_io->incomings, 0), inputs, sizeof(ccv_cnnp_model_io_t) * input_size);
	for (i = 0; i < input_size; i++)
	{
		if (!inputs[i]->outgoings)
			inputs[i]->outgoings = ccv_array_new(sizeof(ccv_cnnp_model_io_t), 1, 0);
		ccv_array_push(inputs[i]->outgoings, &model_io);
	}
	return model_io;
}