#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {TYPE_2__* graph; } ;
struct TYPE_13__ {int nb_filters; TYPE_3__** filters; scalar_t__ execute; TYPE_1__* internal; scalar_t__ thread_type; } ;
struct TYPE_12__ {scalar_t__ thread_execute; } ;
typedef  TYPE_2__ AVFilterGraph ;
typedef  TYPE_3__ AVFilterContext ;
typedef  int /*<<< orphan*/  AVFilter ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  av_err2str (int) ; 
 int /*<<< orphan*/  av_log (TYPE_2__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 TYPE_3__** av_realloc (TYPE_3__**,int) ; 
 int /*<<< orphan*/  avfilter_free (TYPE_3__*) ; 
 TYPE_3__* ff_filter_alloc (int /*<<< orphan*/  const*,char const*) ; 
 int ff_graph_thread_init (TYPE_2__*) ; 

AVFilterContext *avfilter_graph_alloc_filter(AVFilterGraph *graph,
                                             const AVFilter *filter,
                                             const char *name)
{
    AVFilterContext **filters, *s;

    if (graph->thread_type && !graph->internal->thread_execute) {
        if (graph->execute) {
            graph->internal->thread_execute = graph->execute;
        } else {
            int ret = ff_graph_thread_init(graph);
            if (ret < 0) {
                av_log(graph, AV_LOG_ERROR, "Error initializing threading: %s.\n", av_err2str(ret));
                return NULL;
            }
        }
    }

    s = ff_filter_alloc(filter, name);
    if (!s)
        return NULL;

    filters = av_realloc(graph->filters, sizeof(*filters) * (graph->nb_filters + 1));
    if (!filters) {
        avfilter_free(s);
        return NULL;
    }

    graph->filters = filters;
    graph->filters[graph->nb_filters++] = s;

    s->graph = graph;

    return s;
}