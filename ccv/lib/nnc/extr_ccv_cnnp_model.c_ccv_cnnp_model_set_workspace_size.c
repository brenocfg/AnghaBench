#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_2__* compiled_data; } ;
typedef  TYPE_1__ ccv_cnnp_model_t ;
struct TYPE_6__ {size_t workspace_size; scalar_t__ graph; } ;
typedef  TYPE_2__ ccv_cnnp_compiled_data_t ;

/* Variables and functions */
 int /*<<< orphan*/  TRAVERSE_FULL ; 
 int /*<<< orphan*/  assert (TYPE_2__* const) ; 
 int /*<<< orphan*/  ccv_nnc_graph_autotune (scalar_t__,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void ccv_cnnp_model_set_workspace_size(ccv_cnnp_model_t* const model, size_t workspace_size)
{
	ccv_cnnp_compiled_data_t* const compiled_data = model->compiled_data;
	assert(compiled_data);
	if (workspace_size == compiled_data->workspace_size)
		return;
	compiled_data->workspace_size = workspace_size;
	if (compiled_data->graph)
		ccv_nnc_graph_autotune(compiled_data->graph, workspace_size, 0, TRAVERSE_FULL);
}