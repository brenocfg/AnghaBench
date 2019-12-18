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
struct HeadphoneContext {scalar_t__ hrir_fmt; int nb_inputs; } ;
struct TYPE_9__ {TYPE_2__** outputs; TYPE_1__** inputs; struct HeadphoneContext* priv; } ;
struct TYPE_8__ {int /*<<< orphan*/  in_channel_layouts; } ;
struct TYPE_7__ {int /*<<< orphan*/  out_channel_layouts; } ;
typedef  int /*<<< orphan*/  AVFilterFormats ;
typedef  TYPE_3__ AVFilterContext ;
typedef  int /*<<< orphan*/  AVFilterChannelLayouts ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_CH_LAYOUT_STEREO ; 
 int /*<<< orphan*/  AV_SAMPLE_FMT_FLT ; 
 int /*<<< orphan*/  ENOMEM ; 
 scalar_t__ HRIR_MULTI ; 
 int ff_add_channel_layout (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int ff_add_format (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ff_all_channel_counts () ; 
 int /*<<< orphan*/ * ff_all_channel_layouts () ; 
 int /*<<< orphan*/ * ff_all_samplerates () ; 
 int ff_channel_layouts_ref (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int ff_set_common_formats (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int ff_set_common_samplerates (TYPE_3__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int query_formats(AVFilterContext *ctx)
{
    struct HeadphoneContext *s = ctx->priv;
    AVFilterFormats *formats = NULL;
    AVFilterChannelLayouts *layouts = NULL;
    AVFilterChannelLayouts *stereo_layout = NULL;
    AVFilterChannelLayouts *hrir_layouts = NULL;
    int ret, i;

    ret = ff_add_format(&formats, AV_SAMPLE_FMT_FLT);
    if (ret)
        return ret;
    ret = ff_set_common_formats(ctx, formats);
    if (ret)
        return ret;

    layouts = ff_all_channel_layouts();
    if (!layouts)
        return AVERROR(ENOMEM);

    ret = ff_channel_layouts_ref(layouts, &ctx->inputs[0]->out_channel_layouts);
    if (ret)
        return ret;

    ret = ff_add_channel_layout(&stereo_layout, AV_CH_LAYOUT_STEREO);
    if (ret)
        return ret;

    if (s->hrir_fmt == HRIR_MULTI) {
        hrir_layouts = ff_all_channel_counts();
        if (!hrir_layouts)
            return AVERROR(ENOMEM);
        ret = ff_channel_layouts_ref(hrir_layouts, &ctx->inputs[1]->out_channel_layouts);
        if (ret)
            return ret;
    } else {
        for (i = 1; i < s->nb_inputs; i++) {
            ret = ff_channel_layouts_ref(stereo_layout, &ctx->inputs[i]->out_channel_layouts);
            if (ret)
                return ret;
        }
    }

    ret = ff_channel_layouts_ref(stereo_layout, &ctx->outputs[0]->in_channel_layouts);
    if (ret)
        return ret;

    formats = ff_all_samplerates();
    if (!formats)
        return AVERROR(ENOMEM);
    return ff_set_common_samplerates(ctx, formats);
}