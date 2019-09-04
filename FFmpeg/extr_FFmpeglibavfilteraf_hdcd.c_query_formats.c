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
typedef  enum AVSampleFormat { ____Placeholder_AVSampleFormat } AVSampleFormat ;
struct TYPE_7__ {TYPE_1__** outputs; TYPE_1__** inputs; } ;
struct TYPE_6__ {int /*<<< orphan*/  in_formats; int /*<<< orphan*/  out_formats; } ;
typedef  TYPE_1__ AVFilterLink ;
typedef  int /*<<< orphan*/  AVFilterFormats ;
typedef  TYPE_2__ AVFilterContext ;
typedef  int /*<<< orphan*/  AVFilterChannelLayouts ;

/* Variables and functions */
 int /*<<< orphan*/  AV_CH_LAYOUT_MONO ; 
 int /*<<< orphan*/  AV_CH_LAYOUT_STEREO ; 
#define  AV_SAMPLE_FMT_NONE 132 
#define  AV_SAMPLE_FMT_S16 131 
#define  AV_SAMPLE_FMT_S16P 130 
#define  AV_SAMPLE_FMT_S32 129 
#define  AV_SAMPLE_FMT_S32P 128 
 int ff_add_channel_layout (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int ff_formats_ref (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ff_make_format_list (int const*) ; 
 int ff_set_common_channel_layouts (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int ff_set_common_samplerates (TYPE_2__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int query_formats(AVFilterContext *ctx)
{
    static const int sample_rates[] = {
        44100, 48000,
        88200, 96000,
        176400, 192000,
        -1
    };
    AVFilterFormats *in_formats;
    AVFilterFormats *out_formats;
    AVFilterChannelLayouts *layouts = NULL;
    AVFilterLink *inlink  = ctx->inputs[0];
    AVFilterLink *outlink = ctx->outputs[0];

    static const enum AVSampleFormat sample_fmts_in[] = {
        AV_SAMPLE_FMT_S16,
        AV_SAMPLE_FMT_S16P,
        AV_SAMPLE_FMT_S32,
        AV_SAMPLE_FMT_S32P,
        AV_SAMPLE_FMT_NONE
    };
    static const enum AVSampleFormat sample_fmts_out[] = {
        AV_SAMPLE_FMT_S32,
        AV_SAMPLE_FMT_NONE
    };
    int ret;

    ret = ff_add_channel_layout(&layouts, AV_CH_LAYOUT_MONO);
    if (ret < 0)
        return ret;
    ret = ff_add_channel_layout(&layouts, AV_CH_LAYOUT_STEREO);
    if (ret < 0)
        return ret;

    ret = ff_set_common_channel_layouts(ctx, layouts);
    if (ret < 0)
        return ret;

    in_formats = ff_make_format_list(sample_fmts_in);
    ret = ff_formats_ref(in_formats, &inlink->out_formats);
    if (ret < 0)
        return ret;

    out_formats = ff_make_format_list(sample_fmts_out);
    ret = ff_formats_ref(out_formats, &outlink->in_formats);
    if (ret < 0)
        return ret;

    return
        ff_set_common_samplerates(ctx, ff_make_format_list(sample_rates) );
}