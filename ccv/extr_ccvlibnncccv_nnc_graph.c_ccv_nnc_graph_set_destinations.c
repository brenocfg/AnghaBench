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
struct TYPE_3__ {scalar_t__ topsorted; scalar_t__ destinations; int /*<<< orphan*/  sources; } ;
typedef  TYPE_1__ ccv_nnc_graph_t ;
typedef  int /*<<< orphan*/  ccv_nnc_graph_exec_t ;

/* Variables and functions */
 int /*<<< orphan*/  ccv_array_clear (int /*<<< orphan*/ ) ; 
 scalar_t__ ccv_array_new (int,int const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ccv_array_push (scalar_t__,int /*<<< orphan*/  const* const) ; 

void ccv_nnc_graph_set_destinations(ccv_nnc_graph_t* const graph, const ccv_nnc_graph_exec_t* const destinations, const int destination_size)
{
	if (!graph->destinations)
		graph->destinations = ccv_array_new(sizeof(ccv_nnc_graph_exec_t), destination_size, 0);
	else
		ccv_array_clear(graph->sources);
	int i;
	for (i = 0; i < destination_size; i++)
		ccv_array_push(graph->destinations, destinations + i);
	graph->topsorted = 0;
}