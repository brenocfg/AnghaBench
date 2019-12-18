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
struct TYPE_3__ {scalar_t__ destinations; } ;
typedef  TYPE_1__ ccv_nnc_symbolic_graph_t ;
typedef  int /*<<< orphan*/  ccv_nnc_graph_exec_symbol_t ;

/* Variables and functions */
 scalar_t__ ccv_array_get (scalar_t__,int /*<<< orphan*/ ) ; 

ccv_nnc_graph_exec_symbol_t* ccv_nnc_symbolic_graph_destinations(const ccv_nnc_symbolic_graph_t* const graph)
{
	return graph->destinations ? (ccv_nnc_graph_exec_symbol_t*)ccv_array_get(graph->destinations, 0) : 0;
}