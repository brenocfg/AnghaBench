#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_7__ {int /*<<< orphan*/  to; int /*<<< orphan*/  from; } ;
typedef  TYPE_1__ ccv_nnc_graph_tensor_carry_over_t ;
struct TYPE_8__ {TYPE_3__* sub_graphs; TYPE_3__* carry_overs; } ;
typedef  TYPE_2__ ccv_nnc_graph_t ;
struct TYPE_9__ {int rnum; } ;

/* Variables and functions */
 int /*<<< orphan*/  _ccv_nnc_unwrap_tensor_wrap (TYPE_2__ const* const,int /*<<< orphan*/  const,int /*<<< orphan*/  const,int /*<<< orphan*/ ) ; 
 scalar_t__ ccv_array_get (TYPE_3__*,int) ; 

__attribute__((used)) static void _ccv_nnc_graph_unwrap_sub_graph(const ccv_nnc_graph_t* const graph, const int64_t count, const int64_t reverse_count, const ccv_nnc_graph_t* const sub_graph)
{
	int i;
	if (sub_graph->carry_overs)
		for (i = 0; i < sub_graph->carry_overs->rnum; i++)
		{
			ccv_nnc_graph_tensor_carry_over_t* const carry_over = (ccv_nnc_graph_tensor_carry_over_t*)ccv_array_get(sub_graph->carry_overs, i);
			_ccv_nnc_unwrap_tensor_wrap(graph, count, reverse_count, carry_over->from);
			_ccv_nnc_unwrap_tensor_wrap(graph, count, reverse_count, carry_over->to);
		}
	if (sub_graph->sub_graphs)
		for (i = 0; i < sub_graph->sub_graphs->rnum; i++)
			_ccv_nnc_graph_unwrap_sub_graph(graph, count, reverse_count, *(ccv_nnc_graph_t**)ccv_array_get(sub_graph->sub_graphs, i));
}