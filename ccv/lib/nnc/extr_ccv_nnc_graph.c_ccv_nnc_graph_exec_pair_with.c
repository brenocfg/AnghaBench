#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_7__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_7__* exec_info; struct TYPE_8__* pair; } ;
typedef  TYPE_1__ ccv_nnc_graph_t ;
struct TYPE_9__ {scalar_t__ d; TYPE_1__* const graph; } ;
typedef  TYPE_2__ ccv_nnc_graph_exec_t ;
struct TYPE_10__ {scalar_t__ pair_ref; } ;
typedef  TYPE_3__ ccv_nnc_graph_exec_info_t ;
struct TYPE_11__ {scalar_t__ rnum; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ ccv_array_get (TYPE_7__*,scalar_t__) ; 

void ccv_nnc_graph_exec_pair_with(ccv_nnc_graph_t* const graph, const ccv_nnc_graph_exec_t exec, const ccv_nnc_graph_exec_t pair_exec)
{
	assert(exec.graph == graph);
	assert(exec.d >= 0);
	assert(exec.d < graph->exec_info->rnum);
	assert(pair_exec.graph == graph || pair_exec.graph == graph->pair);
	assert(pair_exec.d >= 0);
	if (pair_exec.graph == graph)
		{ assert(pair_exec.d < graph->exec_info->rnum); }
	else
		{ assert(pair_exec.d < graph->pair->exec_info->rnum); }
	ccv_nnc_graph_exec_info_t* const exec_info = (ccv_nnc_graph_exec_info_t*)ccv_array_get(graph->exec_info, exec.d);
	exec_info->pair_ref = pair_exec.d + 1;
}