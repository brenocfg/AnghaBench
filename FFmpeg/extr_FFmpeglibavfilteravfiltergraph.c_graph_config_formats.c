#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  AVFilterGraph ;
typedef  int /*<<< orphan*/  AVClass ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_DEBUG ; 
 int /*<<< orphan*/  EAGAIN ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int pick_formats (int /*<<< orphan*/ *) ; 
 int query_formats (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int reduce_formats (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  swap_channel_layouts (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  swap_sample_fmts (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  swap_samplerates (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int graph_config_formats(AVFilterGraph *graph, AVClass *log_ctx)
{
    int ret;

    /* find supported formats from sub-filters, and merge along links */
    while ((ret = query_formats(graph, log_ctx)) == AVERROR(EAGAIN))
        av_log(graph, AV_LOG_DEBUG, "query_formats not finished\n");
    if (ret < 0)
        return ret;

    /* Once everything is merged, it's possible that we'll still have
     * multiple valid media format choices. We try to minimize the amount
     * of format conversion inside filters */
    if ((ret = reduce_formats(graph)) < 0)
        return ret;

    /* for audio filters, ensure the best format, sample rate and channel layout
     * is selected */
    swap_sample_fmts(graph);
    swap_samplerates(graph);
    swap_channel_layouts(graph);

    if ((ret = pick_formats(graph)) < 0)
        return ret;

    return 0;
}