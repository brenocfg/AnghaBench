#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  enum AVSampleFormat { ____Placeholder_AVSampleFormat } AVSampleFormat ;
typedef  enum AVPixelFormat { ____Placeholder_AVPixelFormat } AVPixelFormat ;
struct TYPE_12__ {TYPE_1__** inputs; TYPE_3__** outputs; TYPE_2__* priv; } ;
struct TYPE_11__ {int /*<<< orphan*/  in_channel_layouts; int /*<<< orphan*/  in_formats; } ;
struct TYPE_10__ {scalar_t__ ir_format; scalar_t__ response; } ;
struct TYPE_9__ {int /*<<< orphan*/  out_channel_layouts; } ;
typedef  TYPE_2__ AudioFIRContext ;
typedef  TYPE_3__ AVFilterLink ;
typedef  int /*<<< orphan*/  AVFilterFormats ;
typedef  TYPE_4__ AVFilterContext ;
typedef  int /*<<< orphan*/  AVFilterChannelLayouts ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_CH_LAYOUT_MONO ; 
#define  AV_PIX_FMT_NONE 131 
#define  AV_PIX_FMT_RGB0 130 
#define  AV_SAMPLE_FMT_FLTP 129 
#define  AV_SAMPLE_FMT_NONE 128 
 int /*<<< orphan*/  ENOMEM ; 
 int ff_add_channel_layout (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ff_all_channel_counts () ; 
 int /*<<< orphan*/ * ff_all_samplerates () ; 
 int ff_channel_layouts_ref (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int ff_formats_ref (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ff_make_format_list (int const*) ; 
 int ff_set_common_channel_layouts (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int ff_set_common_formats (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int ff_set_common_samplerates (TYPE_4__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int query_formats(AVFilterContext *ctx)
{
    AudioFIRContext *s = ctx->priv;
    AVFilterFormats *formats;
    AVFilterChannelLayouts *layouts;
    static const enum AVSampleFormat sample_fmts[] = {
        AV_SAMPLE_FMT_FLTP,
        AV_SAMPLE_FMT_NONE
    };
    static const enum AVPixelFormat pix_fmts[] = {
        AV_PIX_FMT_RGB0,
        AV_PIX_FMT_NONE
    };
    int ret;

    if (s->response) {
        AVFilterLink *videolink = ctx->outputs[1];
        formats = ff_make_format_list(pix_fmts);
        if ((ret = ff_formats_ref(formats, &videolink->in_formats)) < 0)
            return ret;
    }

    layouts = ff_all_channel_counts();
    if (!layouts)
        return AVERROR(ENOMEM);

    if (s->ir_format) {
        ret = ff_set_common_channel_layouts(ctx, layouts);
        if (ret < 0)
            return ret;
    } else {
        AVFilterChannelLayouts *mono = NULL;

        ret = ff_add_channel_layout(&mono, AV_CH_LAYOUT_MONO);
        if (ret)
            return ret;

        if ((ret = ff_channel_layouts_ref(layouts, &ctx->inputs[0]->out_channel_layouts)) < 0)
            return ret;
        if ((ret = ff_channel_layouts_ref(layouts, &ctx->outputs[0]->in_channel_layouts)) < 0)
            return ret;
        if ((ret = ff_channel_layouts_ref(mono, &ctx->inputs[1]->out_channel_layouts)) < 0)
            return ret;
    }

    formats = ff_make_format_list(sample_fmts);
    if ((ret = ff_set_common_formats(ctx, formats)) < 0)
        return ret;

    formats = ff_all_samplerates();
    return ff_set_common_samplerates(ctx, formats);
}