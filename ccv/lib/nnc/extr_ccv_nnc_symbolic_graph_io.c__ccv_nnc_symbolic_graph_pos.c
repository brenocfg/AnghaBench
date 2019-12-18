#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  ccv_nnc_symbolic_graph_t ;

/* Variables and functions */

__attribute__((used)) static ccv_nnc_symbolic_graph_t* _ccv_nnc_symbolic_graph_pos(const int idx)
{
	if (idx < 0)
		return 0; // This is nil.
	return (ccv_nnc_symbolic_graph_t*)(((uintptr_t)idx << 1) + 1);
}