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
typedef  enum AVSampleFormat { ____Placeholder_AVSampleFormat } AVSampleFormat ;
typedef  enum AVPixelFormat { ____Placeholder_AVPixelFormat } AVPixelFormat ;
struct TYPE_7__ {TYPE_2__** outputs; TYPE_1__* priv; TYPE_2__** inputs; } ;
struct TYPE_6__ {int /*<<< orphan*/  in_samplerates; int /*<<< orphan*/  out_samplerates; int /*<<< orphan*/  in_channel_layouts; int /*<<< orphan*/  out_channel_layouts; int /*<<< orphan*/  in_formats; int /*<<< orphan*/  out_formats; } ;
struct TYPE_5__ {scalar_t__ draw_curves; } ;
typedef  TYPE_1__ AudioNEqualizerContext ;
typedef  TYPE_2__ AVFilterLink ;
typedef  int /*<<< orphan*/  AVFilterFormats ;
typedef  TYPE_3__ AVFilterContext ;
typedef  int /*<<< orphan*/  AVFilterChannelLayouts ;

/* Variables and functions */
#define  AV_PIX_FMT_NONE 131 
#define  AV_PIX_FMT_RGBA 130 
#define  AV_SAMPLE_FMT_DBLP 129 
#define  AV_SAMPLE_FMT_NONE 128 
 int /*<<< orphan*/ * ff_all_channel_counts () ; 
 int /*<<< orphan*/ * ff_all_samplerates () ; 
 int ff_channel_layouts_ref (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int ff_formats_ref (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ff_make_format_list (int const*) ; 

__attribute__((used)) static int query_formats(AVFilterContext *ctx)
{
    AVFilterLink *inlink = ctx->inputs[0];
    AVFilterLink *outlink = ctx->outputs[0];
    AudioNEqualizerContext *s = ctx->priv;
    AVFilterFormats *formats;
    AVFilterChannelLayouts *layouts;
    static const enum AVPixelFormat pix_fmts[] = { AV_PIX_FMT_RGBA, AV_PIX_FMT_NONE };
    static const enum AVSampleFormat sample_fmts[] = {
        AV_SAMPLE_FMT_DBLP,
        AV_SAMPLE_FMT_NONE
    };
    int ret;

    if (s->draw_curves) {
        AVFilterLink *videolink = ctx->outputs[1];
        formats = ff_make_format_list(pix_fmts);
        if ((ret = ff_formats_ref(formats, &videolink->in_formats)) < 0)
            return ret;
    }

    formats = ff_make_format_list(sample_fmts);
    if ((ret = ff_formats_ref(formats, &inlink->out_formats)) < 0 ||
        (ret = ff_formats_ref(formats, &outlink->in_formats)) < 0)
        return ret;

    layouts = ff_all_channel_counts();
    if ((ret = ff_channel_layouts_ref(layouts, &inlink->out_channel_layouts)) < 0 ||
        (ret = ff_channel_layouts_ref(layouts, &outlink->in_channel_layouts)) < 0)
        return ret;

    formats = ff_all_samplerates();
    if ((ret = ff_formats_ref(formats, &inlink->out_samplerates)) < 0 ||
        (ret = ff_formats_ref(formats, &outlink->in_samplerates)) < 0)
        return ret;

    return 0;
}