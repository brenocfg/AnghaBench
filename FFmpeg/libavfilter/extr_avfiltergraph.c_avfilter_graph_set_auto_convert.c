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
struct TYPE_3__ {unsigned int disable_auto_convert; } ;
typedef  TYPE_1__ AVFilterGraph ;

/* Variables and functions */

void avfilter_graph_set_auto_convert(AVFilterGraph *graph, unsigned flags)
{
    graph->disable_auto_convert = flags;
}