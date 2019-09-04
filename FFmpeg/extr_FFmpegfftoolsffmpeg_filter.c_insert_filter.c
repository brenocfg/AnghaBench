#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ * graph; } ;
typedef  int /*<<< orphan*/  AVFilterGraph ;
typedef  TYPE_1__ AVFilterContext ;

/* Variables and functions */
 int /*<<< orphan*/  avfilter_get_by_name (char const*) ; 
 int avfilter_graph_create_filter (TYPE_1__**,int /*<<< orphan*/ ,char const*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int avfilter_link (TYPE_1__*,int,TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int insert_filter(AVFilterContext **last_filter, int *pad_idx,
                         const char *filter_name, const char *args)
{
    AVFilterGraph *graph = (*last_filter)->graph;
    AVFilterContext *ctx;
    int ret;

    ret = avfilter_graph_create_filter(&ctx,
                                       avfilter_get_by_name(filter_name),
                                       filter_name, args, NULL, graph);
    if (ret < 0)
        return ret;

    ret = avfilter_link(*last_filter, *pad_idx, ctx, 0);
    if (ret < 0)
        return ret;

    *last_filter = ctx;
    *pad_idx     = 0;
    return 0;
}