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
struct TYPE_10__ {TYPE_2__** outputs; TYPE_2__** inputs; TYPE_1__* priv; } ;
struct TYPE_9__ {int /*<<< orphan*/  in_channel_layouts; int /*<<< orphan*/  out_channel_layouts; } ;
struct TYPE_8__ {int /*<<< orphan*/  nb_output_channels; scalar_t__ out_channel_layout; int /*<<< orphan*/  pure_gains; } ;
typedef  TYPE_1__ PanContext ;
typedef  TYPE_2__ AVFilterLink ;
typedef  int /*<<< orphan*/  AVFilterFormats ;
typedef  TYPE_3__ AVFilterContext ;
typedef  int /*<<< orphan*/  AVFilterChannelLayouts ;

/* Variables and functions */
 int /*<<< orphan*/  AVMEDIA_TYPE_AUDIO ; 
 scalar_t__ FF_COUNT2LAYOUT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  are_gains_pure (TYPE_1__*) ; 
 int ff_add_channel_layout (int /*<<< orphan*/ **,scalar_t__) ; 
 int /*<<< orphan*/ * ff_all_channel_counts () ; 
 int /*<<< orphan*/  ff_all_formats (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ff_all_samplerates () ; 
 int ff_channel_layouts_ref (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int ff_set_common_formats (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int ff_set_common_samplerates (TYPE_3__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int query_formats(AVFilterContext *ctx)
{
    PanContext *pan = ctx->priv;
    AVFilterLink *inlink  = ctx->inputs[0];
    AVFilterLink *outlink = ctx->outputs[0];
    AVFilterFormats *formats = NULL;
    AVFilterChannelLayouts *layouts;
    int ret;

    pan->pure_gains = are_gains_pure(pan);
    /* libswr supports any sample and packing formats */
    if ((ret = ff_set_common_formats(ctx, ff_all_formats(AVMEDIA_TYPE_AUDIO))) < 0)
        return ret;

    formats = ff_all_samplerates();
    if ((ret = ff_set_common_samplerates(ctx, formats)) < 0)
        return ret;

    // inlink supports any channel layout
    layouts = ff_all_channel_counts();
    if ((ret = ff_channel_layouts_ref(layouts, &inlink->out_channel_layouts)) < 0)
        return ret;

    // outlink supports only requested output channel layout
    layouts = NULL;
    if ((ret = ff_add_channel_layout(&layouts,
                          pan->out_channel_layout ? pan->out_channel_layout :
                          FF_COUNT2LAYOUT(pan->nb_output_channels))) < 0)
        return ret;
    return ff_channel_layouts_ref(layouts, &outlink->in_channel_layouts);
}