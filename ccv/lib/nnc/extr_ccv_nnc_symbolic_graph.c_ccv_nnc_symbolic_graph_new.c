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
typedef  int /*<<< orphan*/  ccv_nnc_tensor_symbol_info_t ;
struct TYPE_5__ {int exec; int tensor; } ;
struct TYPE_6__ {TYPE_1__ reuse; void* exec_symbol_info; void* tensor_symbol_info; } ;
typedef  TYPE_2__ ccv_nnc_symbolic_graph_t ;
typedef  int /*<<< orphan*/  ccv_nnc_graph_exec_symbol_info_t ;

/* Variables and functions */
 TYPE_2__* cccalloc (int,int) ; 
 void* ccv_array_new (int,int,int /*<<< orphan*/ ) ; 

ccv_nnc_symbolic_graph_t* ccv_nnc_symbolic_graph_new(void)
{
	ccv_nnc_symbolic_graph_t* graph = cccalloc(1, sizeof(ccv_nnc_symbolic_graph_t));
	graph->tensor_symbol_info = ccv_array_new(sizeof(ccv_nnc_tensor_symbol_info_t), 5, 0);
	graph->exec_symbol_info = ccv_array_new(sizeof(ccv_nnc_graph_exec_symbol_info_t), 5, 0);
	graph->reuse.exec = -1;
	graph->reuse.tensor = -1;
	return graph;
}