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
typedef  int /*<<< orphan*/  ccv_nnc_symbolic_graph_t ;
struct TYPE_3__ {int sub_prep_size; struct TYPE_3__** sub_preps; int /*<<< orphan*/ * graph; int /*<<< orphan*/  const* const symbolic_graph; } ;
typedef  TYPE_1__ ccv_nnc_symbolic_graph_prep_t ;
typedef  int /*<<< orphan*/  ccv_nnc_graph_t ;

/* Variables and functions */

__attribute__((used)) static ccv_nnc_graph_t* _ccv_nnc_graph_find_pair(const ccv_nnc_symbolic_graph_prep_t* const graph_prep, const ccv_nnc_symbolic_graph_t* const pair)
{
	if (graph_prep->symbolic_graph == pair)
		return graph_prep->graph;
	int i;
	for (i = 0; i < graph_prep->sub_prep_size; i++)
		if (graph_prep->sub_preps[i])
		{
			ccv_nnc_graph_t* const graph = _ccv_nnc_graph_find_pair(graph_prep->sub_preps[i], pair);
			if (graph)
				return graph;
		}
	return 0;
}