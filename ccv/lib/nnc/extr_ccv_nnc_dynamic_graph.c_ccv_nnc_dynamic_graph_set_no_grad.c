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
struct TYPE_3__ {int no_grad; } ;
typedef  TYPE_1__ ccv_nnc_dynamic_graph_t ;

/* Variables and functions */

void ccv_nnc_dynamic_graph_set_no_grad(ccv_nnc_dynamic_graph_t* const dynamic_graph, const int no_grad)
{
	dynamic_graph->no_grad = no_grad;
}