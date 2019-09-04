#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* exec_info; } ;
typedef  TYPE_2__ ccv_nnc_graph_t ;
struct TYPE_4__ {int rnum; } ;

/* Variables and functions */

int ccv_nnc_graph_exec_count(const ccv_nnc_graph_t* const graph)
{
	return graph->exec_info ? graph->exec_info->rnum : 0;
}