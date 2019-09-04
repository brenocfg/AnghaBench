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
struct TYPE_3__ {int nb_threads; scalar_t__ thread_type; } ;
typedef  TYPE_1__ AVFilterGraph ;

/* Variables and functions */

int ff_graph_thread_init(AVFilterGraph *graph)
{
    graph->thread_type = 0;
    graph->nb_threads  = 1;
    return 0;
}