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
struct TYPE_10__ {TYPE_1__** outputs; TYPE_2__* priv; } ;
struct TYPE_9__ {int /*<<< orphan*/  channels; int /*<<< orphan*/  channel_layout; int /*<<< orphan*/  sample_rate; int /*<<< orphan*/  sample_fmt; int /*<<< orphan*/  pix_fmt; } ;
struct TYPE_8__ {int type; } ;
typedef  TYPE_2__ BufferSourceContext ;
typedef  int /*<<< orphan*/  AVFilterFormats ;
typedef  TYPE_3__ AVFilterContext ;
typedef  int /*<<< orphan*/  AVFilterChannelLayouts ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
#define  AVMEDIA_TYPE_AUDIO 129 
#define  AVMEDIA_TYPE_VIDEO 128 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  FF_COUNT2LAYOUT (int /*<<< orphan*/ ) ; 
 int ff_add_channel_layout (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int ff_add_format (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int ff_set_common_channel_layouts (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int ff_set_common_formats (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int ff_set_common_samplerates (TYPE_3__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int query_formats(AVFilterContext *ctx)
{
    BufferSourceContext *c = ctx->priv;
    AVFilterChannelLayouts *channel_layouts = NULL;
    AVFilterFormats *formats = NULL;
    AVFilterFormats *samplerates = NULL;
    int ret;

    switch (ctx->outputs[0]->type) {
    case AVMEDIA_TYPE_VIDEO:
        if ((ret = ff_add_format         (&formats, c->pix_fmt)) < 0 ||
            (ret = ff_set_common_formats (ctx     , formats   )) < 0)
            return ret;
        break;
    case AVMEDIA_TYPE_AUDIO:
        if ((ret = ff_add_format             (&formats    , c->sample_fmt )) < 0 ||
            (ret = ff_set_common_formats     (ctx         , formats       )) < 0 ||
            (ret = ff_add_format             (&samplerates, c->sample_rate)) < 0 ||
            (ret = ff_set_common_samplerates (ctx         , samplerates   )) < 0)
            return ret;

        if ((ret = ff_add_channel_layout(&channel_layouts,
                              c->channel_layout ? c->channel_layout :
                              FF_COUNT2LAYOUT(c->channels))) < 0)
            return ret;
        if ((ret = ff_set_common_channel_layouts(ctx, channel_layouts)) < 0)
            return ret;
        break;
    default:
        return AVERROR(EINVAL);
    }

    return 0;
}