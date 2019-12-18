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
struct TYPE_4__ {int /*<<< orphan*/  frame; struct TYPE_4__* settings; int /*<<< orphan*/ * avgraph; } ;
typedef  TYPE_1__ hb_avfilter_graph_t ;

/* Variables and functions */
 int /*<<< orphan*/  av_frame_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avfilter_graph_free (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 

void hb_avfilter_graph_close(hb_avfilter_graph_t ** _g)
{
    hb_avfilter_graph_t * graph = *_g;

    if (graph == NULL)
    {
        return;
    }
    if (graph->avgraph != NULL)
    {
        avfilter_graph_free(&graph->avgraph);
    }
    free(graph->settings);
    av_frame_free(&graph->frame);
    free(graph);
    *_g = NULL;
}