#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int nb_outputs; int /*<<< orphan*/ * outputs; TYPE_1__* priv; } ;
struct TYPE_13__ {TYPE_4__* dst; } ;
struct TYPE_12__ {int channels; int /*<<< orphan*/  channel_layout; int /*<<< orphan*/ * extended_data; int /*<<< orphan*/ * data; } ;
struct TYPE_11__ {size_t* map; } ;
typedef  TYPE_1__ ChannelSplitContext ;
typedef  TYPE_2__ AVFrame ;
typedef  TYPE_3__ AVFilterLink ;
typedef  TYPE_4__ AVFilterContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_channel_layout_extract_channel (int /*<<< orphan*/ ,size_t) ; 
 TYPE_2__* av_frame_clone (TYPE_2__*) ; 
 int /*<<< orphan*/  av_frame_free (TYPE_2__**) ; 
 int ff_filter_frame (int /*<<< orphan*/ ,TYPE_2__*) ; 

__attribute__((used)) static int filter_frame(AVFilterLink *inlink, AVFrame *buf)
{
    AVFilterContext *ctx = inlink->dst;
    ChannelSplitContext *s = ctx->priv;
    int i, ret = 0;

    for (i = 0; i < ctx->nb_outputs; i++) {
        AVFrame *buf_out = av_frame_clone(buf);

        if (!buf_out) {
            ret = AVERROR(ENOMEM);
            break;
        }

        buf_out->data[0] = buf_out->extended_data[0] = buf_out->extended_data[s->map[i]];
        buf_out->channel_layout =
            av_channel_layout_extract_channel(buf->channel_layout, s->map[i]);
        buf_out->channels = 1;

        ret = ff_filter_frame(ctx->outputs[i], buf_out);
        if (ret < 0)
            break;
    }
    av_frame_free(&buf);
    return ret;
}