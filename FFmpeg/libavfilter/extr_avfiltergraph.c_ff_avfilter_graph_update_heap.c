#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  age_index; } ;
typedef  TYPE_1__ AVFilterLink ;
typedef  int /*<<< orphan*/  AVFilterGraph ;

/* Variables and functions */
 int /*<<< orphan*/  heap_bubble_down (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_bubble_up (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 

void ff_avfilter_graph_update_heap(AVFilterGraph *graph, AVFilterLink *link)
{
    heap_bubble_up  (graph, link, link->age_index);
    heap_bubble_down(graph, link, link->age_index);
}