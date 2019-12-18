#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ topsorted; scalar_t__ sources; } ;
typedef  TYPE_1__ ccv_nnc_graph_t ;
typedef  int /*<<< orphan*/  ccv_nnc_graph_exec_t ;

/* Variables and functions */
 int /*<<< orphan*/  ccv_array_clear (scalar_t__) ; 
 scalar_t__ ccv_array_new (int,int const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ccv_array_push (scalar_t__,int /*<<< orphan*/  const* const) ; 

void ccv_nnc_graph_set_sources(ccv_nnc_graph_t* const graph, const ccv_nnc_graph_exec_t* const sources, const int source_size)
{
	if (!graph->sources)
		graph->sources = ccv_array_new(sizeof(ccv_nnc_graph_exec_t), source_size, 0);
	else
		ccv_array_clear(graph->sources);
	int i;
	for (i = 0; i < source_size; i++)
		ccv_array_push(graph->sources, sources + i);
	graph->topsorted = 0;
}