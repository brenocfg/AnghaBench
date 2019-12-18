#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int sub_prep_size; TYPE_3__** sub_preps; } ;
typedef  TYPE_4__ ccv_nnc_symbolic_graph_prep_t ;
struct TYPE_10__ {TYPE_2__* symbolic_graph; TYPE_1__* graph; } ;
struct TYPE_9__ {scalar_t__ pair; } ;
struct TYPE_8__ {int /*<<< orphan*/  pair; } ;

/* Variables and functions */
 int /*<<< orphan*/  _ccv_nnc_graph_find_pair (TYPE_4__ const* const,scalar_t__) ; 

__attribute__((used)) static void _ccv_nnc_graph_fixup_pair(const ccv_nnc_symbolic_graph_prep_t* const root_prep, ccv_nnc_symbolic_graph_prep_t* const graph_prep)
{
	int i;
	for (i = 0; i < graph_prep->sub_prep_size; i++)
		if (graph_prep->sub_preps[i])
		{
			if (graph_prep->sub_preps[i]->symbolic_graph->pair)
				graph_prep->sub_preps[i]->graph->pair = _ccv_nnc_graph_find_pair(root_prep, graph_prep->sub_preps[i]->symbolic_graph->pair);
		}
}