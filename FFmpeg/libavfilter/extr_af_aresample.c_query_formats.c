#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int64_t ;
typedef  enum AVSampleFormat { ____Placeholder_AVSampleFormat } AVSampleFormat ;
struct TYPE_7__ {int /*<<< orphan*/  swr; } ;
struct TYPE_6__ {TYPE_1__** outputs; TYPE_1__** inputs; TYPE_3__* priv; } ;
struct TYPE_5__ {int /*<<< orphan*/  in_channel_layouts; int /*<<< orphan*/  in_formats; int /*<<< orphan*/  in_samplerates; int /*<<< orphan*/  out_channel_layouts; int /*<<< orphan*/  out_samplerates; int /*<<< orphan*/  out_formats; } ;
typedef  TYPE_1__ AVFilterLink ;
typedef  int /*<<< orphan*/  AVFilterFormats ;
typedef  TYPE_2__ AVFilterContext ;
typedef  int /*<<< orphan*/  AVFilterChannelLayouts ;
typedef  TYPE_3__ AResampleContext ;

/* Variables and functions */
 int /*<<< orphan*/  AVMEDIA_TYPE_AUDIO ; 
 int AV_SAMPLE_FMT_NONE ; 
 int /*<<< orphan*/  av_opt_get_int (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  av_opt_get_sample_fmt (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/ * avfilter_make_format64_list (scalar_t__*) ; 
 int /*<<< orphan*/ * ff_all_channel_counts () ; 
 int /*<<< orphan*/ * ff_all_formats (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ff_all_samplerates () ; 
 int ff_channel_layouts_ref (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int ff_formats_ref (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ff_make_format_list (int*) ; 

__attribute__((used)) static int query_formats(AVFilterContext *ctx)
{
    AResampleContext *aresample = ctx->priv;
    enum AVSampleFormat out_format;
    int64_t out_rate, out_layout;

    AVFilterLink *inlink  = ctx->inputs[0];
    AVFilterLink *outlink = ctx->outputs[0];

    AVFilterFormats        *in_formats, *out_formats;
    AVFilterFormats        *in_samplerates, *out_samplerates;
    AVFilterChannelLayouts *in_layouts, *out_layouts;
    int ret;

    av_opt_get_sample_fmt(aresample->swr, "osf", 0, &out_format);
    av_opt_get_int(aresample->swr, "osr", 0, &out_rate);
    av_opt_get_int(aresample->swr, "ocl", 0, &out_layout);

    in_formats      = ff_all_formats(AVMEDIA_TYPE_AUDIO);
    if ((ret = ff_formats_ref(in_formats, &inlink->out_formats)) < 0)
        return ret;

    in_samplerates  = ff_all_samplerates();
    if ((ret = ff_formats_ref(in_samplerates, &inlink->out_samplerates)) < 0)
        return ret;

    in_layouts      = ff_all_channel_counts();
    if ((ret = ff_channel_layouts_ref(in_layouts, &inlink->out_channel_layouts)) < 0)
        return ret;

    if(out_rate > 0) {
        int ratelist[] = { out_rate, -1 };
        out_samplerates = ff_make_format_list(ratelist);
    } else {
        out_samplerates = ff_all_samplerates();
    }

    if ((ret = ff_formats_ref(out_samplerates, &outlink->in_samplerates)) < 0)
        return ret;

    if(out_format != AV_SAMPLE_FMT_NONE) {
        int formatlist[] = { out_format, -1 };
        out_formats = ff_make_format_list(formatlist);
    } else
        out_formats = ff_all_formats(AVMEDIA_TYPE_AUDIO);
    if ((ret = ff_formats_ref(out_formats, &outlink->in_formats)) < 0)
        return ret;

    if(out_layout) {
        int64_t layout_list[] = { out_layout, -1 };
        out_layouts = avfilter_make_format64_list(layout_list);
    } else
        out_layouts = ff_all_channel_counts();

    return ff_channel_layouts_ref(out_layouts, &outlink->in_channel_layouts);
}