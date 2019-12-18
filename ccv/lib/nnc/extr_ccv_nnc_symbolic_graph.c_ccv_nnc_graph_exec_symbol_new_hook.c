#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {void* context; int /*<<< orphan*/  func; } ;
struct TYPE_6__ {TYPE_1__ graph_exec_symbol_new; } ;
struct TYPE_7__ {TYPE_2__ hooks; } ;
typedef  TYPE_3__ ccv_nnc_symbolic_graph_t ;
typedef  int /*<<< orphan*/  ccv_nnc_graph_exec_symbol_new_hook_f ;

/* Variables and functions */

void* ccv_nnc_graph_exec_symbol_new_hook(ccv_nnc_symbolic_graph_t* const graph, ccv_nnc_graph_exec_symbol_new_hook_f hook, void* context)
{
	void* const prev = graph->hooks.graph_exec_symbol_new.context;
	graph->hooks.graph_exec_symbol_new.func = hook;
	graph->hooks.graph_exec_symbol_new.context = context;
	return prev;
}