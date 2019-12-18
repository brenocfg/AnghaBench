#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_8__ ;
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int /*<<< orphan*/  den; int /*<<< orphan*/  num; } ;
struct TYPE_14__ {int /*<<< orphan*/  den; int /*<<< orphan*/  num; } ;
struct TYPE_11__ {scalar_t__ num; scalar_t__ den; } ;
struct TYPE_18__ {int /*<<< orphan*/  channel_layout; int /*<<< orphan*/  sample_rate; int /*<<< orphan*/  format; int /*<<< orphan*/  hw_frames_ctx; TYPE_5__ frame_rate; TYPE_4__ sample_aspect_ratio; int /*<<< orphan*/  height; int /*<<< orphan*/  width; TYPE_1__ time_base; } ;
struct TYPE_17__ {TYPE_3__* filter; TYPE_6__* priv; } ;
struct TYPE_16__ {int got_format_from_params; int /*<<< orphan*/  channel_layout; int /*<<< orphan*/  sample_rate; int /*<<< orphan*/  sample_fmt; int /*<<< orphan*/  hw_frames_ctx; TYPE_5__ frame_rate; TYPE_4__ pixel_aspect; int /*<<< orphan*/  h; int /*<<< orphan*/  w; int /*<<< orphan*/  pix_fmt; TYPE_1__ time_base; } ;
struct TYPE_13__ {TYPE_2__* outputs; } ;
struct TYPE_12__ {int type; } ;
typedef  TYPE_6__ BufferSourceContext ;
typedef  TYPE_7__ AVFilterContext ;
typedef  TYPE_8__ AVBufferSrcParameters ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_BUG ; 
#define  AVMEDIA_TYPE_AUDIO 129 
#define  AVMEDIA_TYPE_VIDEO 128 
 int /*<<< orphan*/  AV_PIX_FMT_NONE ; 
 int /*<<< orphan*/  AV_SAMPLE_FMT_NONE ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_buffer_ref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_buffer_unref (int /*<<< orphan*/ *) ; 

int av_buffersrc_parameters_set(AVFilterContext *ctx, AVBufferSrcParameters *param)
{
    BufferSourceContext *s = ctx->priv;

    if (param->time_base.num > 0 && param->time_base.den > 0)
        s->time_base = param->time_base;

    switch (ctx->filter->outputs[0].type) {
    case AVMEDIA_TYPE_VIDEO:
        if (param->format != AV_PIX_FMT_NONE) {
            s->got_format_from_params = 1;
            s->pix_fmt = param->format;
        }
        if (param->width > 0)
            s->w = param->width;
        if (param->height > 0)
            s->h = param->height;
        if (param->sample_aspect_ratio.num > 0 && param->sample_aspect_ratio.den > 0)
            s->pixel_aspect = param->sample_aspect_ratio;
        if (param->frame_rate.num > 0 && param->frame_rate.den > 0)
            s->frame_rate = param->frame_rate;
        if (param->hw_frames_ctx) {
            av_buffer_unref(&s->hw_frames_ctx);
            s->hw_frames_ctx = av_buffer_ref(param->hw_frames_ctx);
            if (!s->hw_frames_ctx)
                return AVERROR(ENOMEM);
        }
        break;
    case AVMEDIA_TYPE_AUDIO:
        if (param->format != AV_SAMPLE_FMT_NONE) {
            s->got_format_from_params = 1;
            s->sample_fmt = param->format;
        }
        if (param->sample_rate > 0)
            s->sample_rate = param->sample_rate;
        if (param->channel_layout)
            s->channel_layout = param->channel_layout;
        break;
    default:
        return AVERROR_BUG;
    }

    return 0;
}