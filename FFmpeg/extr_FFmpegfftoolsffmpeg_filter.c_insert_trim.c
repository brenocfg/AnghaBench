#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int64_t ;
typedef  enum AVMediaType { ____Placeholder_AVMediaType } AVMediaType ;
struct TYPE_9__ {int /*<<< orphan*/  output_pads; int /*<<< orphan*/ * graph; } ;
typedef  int /*<<< orphan*/  AVFilterGraph ;
typedef  TYPE_1__ AVFilterContext ;
typedef  int /*<<< orphan*/  AVFilter ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_FILTER_NOT_FOUND ; 
 int AVMEDIA_TYPE_VIDEO ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_NOPTS_VALUE ; 
 int /*<<< orphan*/  AV_OPT_SEARCH_CHILDREN ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  INT64_MAX ; 
 int /*<<< orphan*/  av_log (TYPE_1__*,int /*<<< orphan*/ ,char*,char const*) ; 
 int av_opt_set_int (TYPE_1__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * avfilter_get_by_name (char const*) ; 
 TYPE_1__* avfilter_graph_alloc_filter (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,char const*) ; 
 int avfilter_init_str (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int avfilter_link (TYPE_1__*,int,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int avfilter_pad_get_type (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int insert_trim(int64_t start_time, int64_t duration,
                       AVFilterContext **last_filter, int *pad_idx,
                       const char *filter_name)
{
    AVFilterGraph *graph = (*last_filter)->graph;
    AVFilterContext *ctx;
    const AVFilter *trim;
    enum AVMediaType type = avfilter_pad_get_type((*last_filter)->output_pads, *pad_idx);
    const char *name = (type == AVMEDIA_TYPE_VIDEO) ? "trim" : "atrim";
    int ret = 0;

    if (duration == INT64_MAX && start_time == AV_NOPTS_VALUE)
        return 0;

    trim = avfilter_get_by_name(name);
    if (!trim) {
        av_log(NULL, AV_LOG_ERROR, "%s filter not present, cannot limit "
               "recording time.\n", name);
        return AVERROR_FILTER_NOT_FOUND;
    }

    ctx = avfilter_graph_alloc_filter(graph, trim, filter_name);
    if (!ctx)
        return AVERROR(ENOMEM);

    if (duration != INT64_MAX) {
        ret = av_opt_set_int(ctx, "durationi", duration,
                                AV_OPT_SEARCH_CHILDREN);
    }
    if (ret >= 0 && start_time != AV_NOPTS_VALUE) {
        ret = av_opt_set_int(ctx, "starti", start_time,
                                AV_OPT_SEARCH_CHILDREN);
    }
    if (ret < 0) {
        av_log(ctx, AV_LOG_ERROR, "Error configuring the %s filter", name);
        return ret;
    }

    ret = avfilter_init_str(ctx, NULL);
    if (ret < 0)
        return ret;

    ret = avfilter_link(*last_filter, *pad_idx, ctx, 0);
    if (ret < 0)
        return ret;

    *last_filter = ctx;
    *pad_idx     = 0;
    return 0;
}