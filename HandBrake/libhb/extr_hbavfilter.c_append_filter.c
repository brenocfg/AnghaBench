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
struct TYPE_3__ {int /*<<< orphan*/ * last; int /*<<< orphan*/  avgraph; } ;
typedef  TYPE_1__ hb_avfilter_graph_t ;
typedef  int /*<<< orphan*/  AVFilterContext ;

/* Variables and functions */
 int /*<<< orphan*/  avfilter_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avfilter_get_by_name (char const*) ; 
 int avfilter_graph_create_filter (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char const*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int avfilter_link (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static AVFilterContext * append_filter( hb_avfilter_graph_t * graph,
                                        const char * name, const char * args)
{
    AVFilterContext * filter;
    int               result;

    result = avfilter_graph_create_filter(&filter, avfilter_get_by_name(name),
                                          name, args, NULL, graph->avgraph);
    if (result < 0)
    {
        return NULL;
    }
    if (graph->last != NULL)
    {
        result = avfilter_link(graph->last, 0, filter, 0);
        if (result < 0)
        {
            avfilter_free(filter);
            return NULL;
        }
    }
    graph->last = filter;

    return filter;
}