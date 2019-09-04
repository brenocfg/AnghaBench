#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  enum AVSampleFormat { ____Placeholder_AVSampleFormat } AVSampleFormat ;
struct TYPE_9__ {TYPE_2__** outputs; TYPE_2__** inputs; TYPE_1__* priv; } ;
struct TYPE_8__ {int /*<<< orphan*/  in_samplerates; int /*<<< orphan*/  out_samplerates; } ;
struct TYPE_7__ {scalar_t__ frame_type; } ;
typedef  TYPE_1__ LoudNormContext ;
typedef  TYPE_2__ AVFilterLink ;
typedef  int /*<<< orphan*/  AVFilterFormats ;
typedef  TYPE_3__ AVFilterContext ;
typedef  int /*<<< orphan*/  AVFilterChannelLayouts ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
#define  AV_SAMPLE_FMT_DBL 129 
#define  AV_SAMPLE_FMT_NONE 128 
 int /*<<< orphan*/  ENOMEM ; 
 scalar_t__ LINEAR_MODE ; 
 int /*<<< orphan*/ * ff_all_channel_counts () ; 
 int ff_formats_ref (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ff_make_format_list (int const*) ; 
 int ff_set_common_channel_layouts (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int ff_set_common_formats (TYPE_3__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int query_formats(AVFilterContext *ctx)
{
    LoudNormContext *s = ctx->priv;
    AVFilterFormats *formats;
    AVFilterChannelLayouts *layouts;
    AVFilterLink *inlink = ctx->inputs[0];
    AVFilterLink *outlink = ctx->outputs[0];
    static const int input_srate[] = {192000, -1};
    static const enum AVSampleFormat sample_fmts[] = {
        AV_SAMPLE_FMT_DBL,
        AV_SAMPLE_FMT_NONE
    };
    int ret;

    layouts = ff_all_channel_counts();
    if (!layouts)
        return AVERROR(ENOMEM);
    ret = ff_set_common_channel_layouts(ctx, layouts);
    if (ret < 0)
        return ret;

    formats = ff_make_format_list(sample_fmts);
    if (!formats)
        return AVERROR(ENOMEM);
    ret = ff_set_common_formats(ctx, formats);
    if (ret < 0)
        return ret;

    if (s->frame_type != LINEAR_MODE) {
        formats = ff_make_format_list(input_srate);
        if (!formats)
            return AVERROR(ENOMEM);
        ret = ff_formats_ref(formats, &inlink->out_samplerates);
        if (ret < 0)
            return ret;
        ret = ff_formats_ref(formats, &outlink->in_samplerates);
        if (ret < 0)
            return ret;
    }

    return 0;
}