#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {TYPE_1__* exec_info; } ;
typedef  TYPE_4__ ccv_nnc_graph_t ;
struct TYPE_14__ {int d; TYPE_4__* const graph; } ;
typedef  TYPE_5__ ccv_nnc_graph_exec_t ;
struct TYPE_12__ {int d; } ;
struct TYPE_11__ {int d; } ;
struct TYPE_15__ {int graph_exec_size; TYPE_5__* graph_execs; TYPE_3__ destination; TYPE_2__ source; } ;
typedef  TYPE_6__ ccv_nnc_graph_exec_arena_t ;
struct TYPE_10__ {int rnum; } ;

/* Variables and functions */
 int /*<<< orphan*/  ccfree (int* const) ; 
 scalar_t__ ccmalloc (int) ; 
 int /*<<< orphan*/  ccv_nnc_graph_topsort (TYPE_4__* const,int* const,int) ; 

__attribute__((used)) static void _ccv_nnc_graph_exec_arena_topsort(ccv_nnc_graph_t* const graph, ccv_nnc_graph_exec_arena_t* const graph_exec_arena)
{
	int i;
	int* const exec_cvt = (int*)ccmalloc(sizeof(int) * graph->exec_info->rnum);
	ccv_nnc_graph_topsort(graph, exec_cvt, graph->exec_info->rnum);
	graph_exec_arena->source.d = exec_cvt[graph_exec_arena->source.d];
	graph_exec_arena->destination.d = exec_cvt[graph_exec_arena->destination.d];
	ccv_nnc_graph_exec_t* const graph_execs = graph_exec_arena->graph_execs;
	for (i = 0; i < graph_exec_arena->graph_exec_size; i++)
		if (graph_execs[i].graph == graph)
			graph_execs[i].d = exec_cvt[graph_execs[i].d];
	ccfree(exec_cvt);
}