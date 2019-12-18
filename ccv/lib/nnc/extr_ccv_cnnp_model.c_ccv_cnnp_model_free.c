#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {struct TYPE_10__* const name; scalar_t__ compiled_data; scalar_t__ graph; struct TYPE_10__* const inputs; TYPE_6__* io; TYPE_6__* incomings; TYPE_6__* outgoings; TYPE_1__* isa; } ;
typedef  TYPE_2__ ccv_cnnp_model_t ;
typedef  TYPE_2__* ccv_cnnp_model_io_t ;
struct TYPE_11__ {int rnum; } ;
struct TYPE_9__ {int /*<<< orphan*/  (* deinit ) (TYPE_2__* const) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  _ccv_cnnp_compiled_data_free (scalar_t__) ; 
 int /*<<< orphan*/  ccfree (TYPE_2__* const) ; 
 int /*<<< orphan*/  ccv_array_free (TYPE_6__*) ; 
 scalar_t__ ccv_array_get (TYPE_6__*,int) ; 
 int /*<<< orphan*/  ccv_nnc_symbolic_graph_free (scalar_t__) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__* const) ; 

void ccv_cnnp_model_free(ccv_cnnp_model_t* const model)
{
	if (model->isa->deinit)
		model->isa->deinit(model);
	if (model->io)
	{
		int i;
		for (i = 0; i < model->io->rnum; i++)
		{
			ccv_cnnp_model_io_t model_io = *(ccv_cnnp_model_io_t*)ccv_array_get(model->io, i);
			if (model_io->outgoings)
				ccv_array_free(model_io->outgoings);
			if (model_io->incomings)
				ccv_array_free(model_io->incomings);
			ccfree(model_io);
		}
		ccv_array_free(model->io);
	}
	if (model->inputs)
		ccfree(model->inputs);
	if (model->graph)
		ccv_nnc_symbolic_graph_free(model->graph);
	if (model->compiled_data)
		_ccv_cnnp_compiled_data_free(model->compiled_data);
	if (model->name)
		ccfree(model->name);
	ccfree(model);
}