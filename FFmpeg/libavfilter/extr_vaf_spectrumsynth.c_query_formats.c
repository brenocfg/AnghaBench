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
struct TYPE_7__ {TYPE_2__** outputs; TYPE_2__** inputs; TYPE_1__* priv; } ;
struct TYPE_6__ {int /*<<< orphan*/  out_formats; int /*<<< orphan*/  in_samplerates; int /*<<< orphan*/  in_channel_layouts; int /*<<< orphan*/  in_formats; } ;
struct TYPE_5__ {int sample_rate; int /*<<< orphan*/  channels; } ;
typedef  TYPE_1__ SpectrumSynthContext ;
typedef  TYPE_2__ AVFilterLink ;
typedef  int /*<<< orphan*/  AVFilterFormats ;
typedef  TYPE_3__ AVFilterContext ;
typedef  int /*<<< orphan*/  AVFilterChannelLayouts ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
#define  AV_PIX_FMT_GRAY16 135 
#define  AV_PIX_FMT_GRAY8 134 
#define  AV_PIX_FMT_NONE 133 
#define  AV_PIX_FMT_YUV444P 132 
#define  AV_PIX_FMT_YUV444P16 131 
#define  AV_PIX_FMT_YUVJ444P 130 
#define  AV_SAMPLE_FMT_FLTP 129 
#define  AV_SAMPLE_FMT_NONE 128 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  FF_COUNT2LAYOUT (int /*<<< orphan*/ ) ; 
 int ff_add_channel_layout (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int ff_channel_layouts_ref (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int ff_formats_ref (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ff_make_format_list (int const*) ; 

__attribute__((used)) static int query_formats(AVFilterContext *ctx)
{
    SpectrumSynthContext *s = ctx->priv;
    AVFilterFormats *formats = NULL;
    AVFilterChannelLayouts *layout = NULL;
    AVFilterLink *magnitude = ctx->inputs[0];
    AVFilterLink *phase = ctx->inputs[1];
    AVFilterLink *outlink = ctx->outputs[0];
    static const enum AVSampleFormat sample_fmts[] = { AV_SAMPLE_FMT_FLTP, AV_SAMPLE_FMT_NONE };
    static const enum AVPixelFormat pix_fmts[] = { AV_PIX_FMT_GRAY8, AV_PIX_FMT_GRAY16,
                                                   AV_PIX_FMT_YUV444P, AV_PIX_FMT_YUVJ444P,
                                                   AV_PIX_FMT_YUV444P16, AV_PIX_FMT_NONE };
    int ret, sample_rates[] = { 48000, -1 };

    formats = ff_make_format_list(sample_fmts);
    if ((ret = ff_formats_ref         (formats, &outlink->in_formats        )) < 0 ||
        (ret = ff_add_channel_layout  (&layout, FF_COUNT2LAYOUT(s->channels))) < 0 ||
        (ret = ff_channel_layouts_ref (layout , &outlink->in_channel_layouts)) < 0)
        return ret;

    sample_rates[0] = s->sample_rate;
    formats = ff_make_format_list(sample_rates);
    if (!formats)
        return AVERROR(ENOMEM);
    if ((ret = ff_formats_ref(formats, &outlink->in_samplerates)) < 0)
        return ret;

    formats = ff_make_format_list(pix_fmts);
    if (!formats)
        return AVERROR(ENOMEM);
    if ((ret = ff_formats_ref(formats, &magnitude->out_formats)) < 0)
        return ret;

    formats = ff_make_format_list(pix_fmts);
    if (!formats)
        return AVERROR(ENOMEM);
    if ((ret = ff_formats_ref(formats, &phase->out_formats)) < 0)
        return ret;

    return 0;
}