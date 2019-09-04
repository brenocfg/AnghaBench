#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  enum AVSampleFormat { ____Placeholder_AVSampleFormat } AVSampleFormat ;
struct TYPE_10__ {TYPE_1__* priv; TYPE_2__** outputs; TYPE_2__** inputs; } ;
struct TYPE_9__ {int /*<<< orphan*/  in_channel_layouts; int /*<<< orphan*/  out_channel_layouts; } ;
struct TYPE_8__ {int /*<<< orphan*/  nb_channels; scalar_t__ out_channel_layout; scalar_t__ same_chlayout; } ;
typedef  TYPE_1__ EvalContext ;
typedef  TYPE_2__ AVFilterLink ;
typedef  int /*<<< orphan*/  AVFilterFormats ;
typedef  TYPE_3__ AVFilterContext ;
typedef  int /*<<< orphan*/  AVFilterChannelLayouts ;

/* Variables and functions */
#define  AV_SAMPLE_FMT_DBLP 129 
#define  AV_SAMPLE_FMT_NONE 128 
 scalar_t__ FF_COUNT2LAYOUT (int /*<<< orphan*/ ) ; 
 int ff_add_channel_layout (int /*<<< orphan*/ **,scalar_t__) ; 
 int /*<<< orphan*/ * ff_all_channel_counts () ; 
 int /*<<< orphan*/ * ff_all_samplerates () ; 
 int ff_channel_layouts_ref (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ff_make_format_list (int const*) ; 
 int ff_set_common_channel_layouts (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int ff_set_common_formats (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int ff_set_common_samplerates (TYPE_3__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int aeval_query_formats(AVFilterContext *ctx)
{
    AVFilterFormats *formats = NULL;
    AVFilterChannelLayouts *layouts;
    AVFilterLink *inlink  = ctx->inputs[0];
    AVFilterLink *outlink  = ctx->outputs[0];
    EvalContext *eval = ctx->priv;
    static const enum AVSampleFormat sample_fmts[] = {
        AV_SAMPLE_FMT_DBLP, AV_SAMPLE_FMT_NONE
    };
    int ret;

    // inlink supports any channel layout
    layouts = ff_all_channel_counts();
    if ((ret = ff_channel_layouts_ref(layouts, &inlink->out_channel_layouts)) < 0)
        return ret;

    if (eval->same_chlayout) {
        layouts = ff_all_channel_counts();
        if ((ret = ff_set_common_channel_layouts(ctx, layouts)) < 0)
            return ret;
    } else {
        // outlink supports only requested output channel layout
        layouts = NULL;
        if ((ret = ff_add_channel_layout(&layouts,
                              eval->out_channel_layout ? eval->out_channel_layout :
                              FF_COUNT2LAYOUT(eval->nb_channels))) < 0)
            return ret;
        if ((ret = ff_channel_layouts_ref(layouts, &outlink->in_channel_layouts)) < 0)
            return ret;
    }

    formats = ff_make_format_list(sample_fmts);
    if ((ret = ff_set_common_formats(ctx, formats)) < 0)
        return ret;

    formats = ff_all_samplerates();
    return ff_set_common_samplerates(ctx, formats);
}