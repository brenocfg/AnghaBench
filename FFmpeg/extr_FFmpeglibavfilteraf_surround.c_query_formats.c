#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {TYPE_2__** inputs; TYPE_1__** outputs; TYPE_3__* priv; } ;
struct TYPE_10__ {int /*<<< orphan*/  in_channel_layout; int /*<<< orphan*/  out_channel_layout; } ;
struct TYPE_9__ {int /*<<< orphan*/  out_channel_layouts; } ;
struct TYPE_8__ {int /*<<< orphan*/  in_channel_layouts; } ;
typedef  TYPE_3__ AudioSurroundContext ;
typedef  int /*<<< orphan*/  AVFilterFormats ;
typedef  TYPE_4__ AVFilterContext ;
typedef  int /*<<< orphan*/  AVFilterChannelLayouts ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_SAMPLE_FMT_FLTP ; 
 int /*<<< orphan*/  ENOMEM ; 
 int ff_add_channel_layout (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int ff_add_format (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ff_all_samplerates () ; 
 int ff_channel_layouts_ref (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int ff_set_common_formats (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int ff_set_common_samplerates (TYPE_4__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int query_formats(AVFilterContext *ctx)
{
    AudioSurroundContext *s = ctx->priv;
    AVFilterFormats *formats = NULL;
    AVFilterChannelLayouts *layouts = NULL;
    int ret;

    ret = ff_add_format(&formats, AV_SAMPLE_FMT_FLTP);
    if (ret)
        return ret;
    ret = ff_set_common_formats(ctx, formats);
    if (ret)
        return ret;

    layouts = NULL;
    ret = ff_add_channel_layout(&layouts, s->out_channel_layout);
    if (ret)
        return ret;

    ret = ff_channel_layouts_ref(layouts, &ctx->outputs[0]->in_channel_layouts);
    if (ret)
        return ret;

    layouts = NULL;
    ret = ff_add_channel_layout(&layouts, s->in_channel_layout);
    if (ret)
        return ret;

    ret = ff_channel_layouts_ref(layouts, &ctx->inputs[0]->out_channel_layouts);
    if (ret)
        return ret;

    formats = ff_all_samplerates();
    if (!formats)
        return AVERROR(ENOMEM);
    return ff_set_common_samplerates(ctx, formats);
}