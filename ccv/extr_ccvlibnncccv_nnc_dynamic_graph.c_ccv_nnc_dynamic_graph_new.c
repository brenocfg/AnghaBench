#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ccv_nnc_tensor_variable_t ;
typedef  int /*<<< orphan*/  ccv_nnc_tensor_variable_graph_bind_t ;
struct TYPE_4__ {int reuse_var; scalar_t__ ws; int /*<<< orphan*/  tape; void* binds; void* vars; } ;
typedef  TYPE_1__ ccv_nnc_dynamic_graph_t ;

/* Variables and functions */
 TYPE_1__* ccmalloc (int) ; 
 void* ccv_array_new (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ccv_nnc_symbolic_graph_new () ; 

ccv_nnc_dynamic_graph_t* ccv_nnc_dynamic_graph_new(void)
{
	ccv_nnc_dynamic_graph_t* graph = ccmalloc(sizeof(ccv_nnc_dynamic_graph_t));
	graph->reuse_var = -1;
	graph->vars = ccv_array_new(sizeof(ccv_nnc_tensor_variable_t), 1, 0);
	graph->binds = ccv_array_new(sizeof(ccv_nnc_tensor_variable_graph_bind_t), 1, 0);
	graph->tape = ccv_nnc_symbolic_graph_new();
	graph->ws = 0;
	return graph;
}