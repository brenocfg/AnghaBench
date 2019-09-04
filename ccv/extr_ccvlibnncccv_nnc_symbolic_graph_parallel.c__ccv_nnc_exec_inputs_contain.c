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
struct TYPE_3__ {int input_size; int const* inputs; } ;
typedef  TYPE_1__ ccv_nnc_graph_exec_symbol_info_t ;

/* Variables and functions */

__attribute__((used)) static int _ccv_nnc_exec_inputs_contain(const ccv_nnc_graph_exec_symbol_info_t* const node, const int d)
{
	int i;
	for (i = 0; i < node->input_size; i++)
		if (node->inputs[i] == d)
			return 1;
	return 0;
}