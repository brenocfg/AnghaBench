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
struct TYPE_3__ {int /*<<< orphan*/  tape; } ;
typedef  TYPE_1__ ccv_nnc_dynamic_graph_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  ccv_nnc_symbolic_graph_dot (int /*<<< orphan*/ ,int const,int /*<<< orphan*/ *) ; 

void ccv_nnc_dynamic_graph_dot(const ccv_nnc_dynamic_graph_t* const graph, const int flags, FILE* out)
{
	ccv_nnc_symbolic_graph_dot(graph->tape, flags, out);
}