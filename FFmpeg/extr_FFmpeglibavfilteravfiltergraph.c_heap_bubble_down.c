#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int sink_links_count; TYPE_1__** sink_links; } ;
struct TYPE_5__ {scalar_t__ current_pts_us; int age_index; } ;
typedef  TYPE_1__ AVFilterLink ;
typedef  TYPE_2__ AVFilterGraph ;

/* Variables and functions */
 int /*<<< orphan*/  av_assert0 (int) ; 

__attribute__((used)) static void heap_bubble_down(AVFilterGraph *graph,
                             AVFilterLink *link, int index)
{
    AVFilterLink **links = graph->sink_links;

    av_assert0(index >= 0);

    while (1) {
        int child = 2 * index + 1;
        if (child >= graph->sink_links_count)
            break;
        if (child + 1 < graph->sink_links_count &&
            links[child + 1]->current_pts_us < links[child]->current_pts_us)
            child++;
        if (link->current_pts_us < links[child]->current_pts_us)
            break;
        links[index] = links[child];
        links[index]->age_index = index;
        index = child;
    }
    links[index] = link;
    link->age_index = index;
}