#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  enum AVMediaType { ____Placeholder_AVMediaType } AVMediaType ;
struct TYPE_7__ {int /*<<< orphan*/  output_pads; } ;
struct TYPE_6__ {int /*<<< orphan*/  sink; } ;
typedef  TYPE_1__ Stream ;
typedef  int /*<<< orphan*/  AVFilterGraph ;
typedef  TYPE_2__ AVFilterContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
#define  AVMEDIA_TYPE_AUDIO 129 
#define  AVMEDIA_TYPE_VIDEO 128 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  avfilter_get_by_name (char const*) ; 
 int avfilter_graph_create_filter (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int avfilter_link (TYPE_2__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int avfilter_pad_get_type (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int create_sink(Stream *st, AVFilterGraph *graph,
                       AVFilterContext *f, int idx)
{
    enum AVMediaType type = avfilter_pad_get_type(f->output_pads, idx);
    const char *sink_name;
    int ret;

    switch (type) {
    case AVMEDIA_TYPE_VIDEO: sink_name =  "buffersink"; break;
    case AVMEDIA_TYPE_AUDIO: sink_name = "abuffersink"; break;
    default:
        av_log(NULL, AV_LOG_ERROR, "Stream type not supported\n");
        return AVERROR(EINVAL);
    }
    ret = avfilter_graph_create_filter(&st->sink,
                                       avfilter_get_by_name(sink_name),
                                       NULL, NULL, NULL, graph);
    if (ret < 0)
        return ret;
    ret = avfilter_link(f, idx, st->sink, 0);
    if (ret < 0)
        return ret;
    return 0;
}