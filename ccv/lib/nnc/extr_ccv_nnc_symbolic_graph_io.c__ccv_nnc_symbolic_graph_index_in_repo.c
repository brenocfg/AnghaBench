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
typedef  int /*<<< orphan*/  const ccv_nnc_symbolic_graph_t ;
struct TYPE_4__ {int rnum; } ;
typedef  TYPE_1__ ccv_array_t ;

/* Variables and functions */
 scalar_t__ ccv_array_get (TYPE_1__ const* const,int) ; 

__attribute__((used)) static int _ccv_nnc_symbolic_graph_index_in_repo(const ccv_nnc_symbolic_graph_t* const graph, const ccv_array_t* const repo)
{
	if (!graph)
		return -1;
	int i;
	for (i = 0; i < repo->rnum; i++)
		if (*(ccv_nnc_symbolic_graph_t**)ccv_array_get(repo, i) == graph)
			return i;
	return -1;
}