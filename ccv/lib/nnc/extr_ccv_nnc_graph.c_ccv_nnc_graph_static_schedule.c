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
struct TYPE_4__ {scalar_t__ p; } ;
typedef  TYPE_1__ ccv_nnc_graph_t ;

/* Variables and functions */
 int /*<<< orphan*/  _ccv_nnc_graph_static_schedule (TYPE_1__* const,int const,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 

void ccv_nnc_graph_static_schedule(ccv_nnc_graph_t* const graph, const int stream_type)
{
	assert(graph->p == 0);
	_ccv_nnc_graph_static_schedule(graph, stream_type, -1, 0);
}