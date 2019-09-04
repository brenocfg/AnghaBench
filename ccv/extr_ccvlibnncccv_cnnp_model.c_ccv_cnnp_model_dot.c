#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* compiled_data; scalar_t__ graph; } ;
typedef  TYPE_2__ ccv_cnnp_model_t ;
struct TYPE_4__ {scalar_t__ graph; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  ccv_nnc_graph_dot (scalar_t__,int const,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ccv_nnc_symbolic_graph_dot (scalar_t__,int const,int /*<<< orphan*/ *) ; 

void ccv_cnnp_model_dot(const ccv_cnnp_model_t* const model, const int flags, FILE* out)
{
	if (model->graph)
		ccv_nnc_symbolic_graph_dot(model->graph, flags, out);
	if (model->compiled_data && model->compiled_data->graph)
		ccv_nnc_graph_dot(model->compiled_data->graph, flags, out);
}