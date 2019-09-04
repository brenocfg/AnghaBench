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
typedef  int /*<<< orphan*/  ccv_nnc_graph_exec_t ;
struct TYPE_3__ {int /*<<< orphan*/  destination; } ;
typedef  TYPE_1__ ccv_nnc_graph_exec_arena_t ;

/* Variables and functions */

ccv_nnc_graph_exec_t ccv_nnc_graph_exec_destination(const ccv_nnc_graph_exec_arena_t* const graph_exec_arena)
{
	return graph_exec_arena->destination;
}