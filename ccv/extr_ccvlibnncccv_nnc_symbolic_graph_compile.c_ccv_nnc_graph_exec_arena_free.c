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
struct TYPE_4__ {int sub_arena_size; struct TYPE_4__** sub_arenas; } ;
typedef  TYPE_1__ ccv_nnc_graph_exec_arena_t ;

/* Variables and functions */
 int /*<<< orphan*/  ccfree (TYPE_1__* const) ; 

void ccv_nnc_graph_exec_arena_free(ccv_nnc_graph_exec_arena_t* const graph_exec_arena)
{
	int i;
	for (i = 0; i < graph_exec_arena->sub_arena_size; i++)
		if (graph_exec_arena->sub_arenas[i])
			ccv_nnc_graph_exec_arena_free(graph_exec_arena->sub_arenas[i]);
	ccfree(graph_exec_arena);
}