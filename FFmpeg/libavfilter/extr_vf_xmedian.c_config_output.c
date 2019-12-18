#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;
typedef  struct TYPE_12__   TYPE_10__ ;

/* Type definitions */
struct TYPE_18__ {int /*<<< orphan*/  time_base; int /*<<< orphan*/  on_event; TYPE_2__* opaque; TYPE_3__* in; } ;
struct TYPE_14__ {int nb_inputs; int depth; int max; int* width; int* height; TYPE_6__ fs; TYPE_10__* desc; int /*<<< orphan*/  linesize; int /*<<< orphan*/  median_frames; int /*<<< orphan*/  nb_planes; } ;
typedef  TYPE_2__ XMedianContext ;
struct TYPE_17__ {TYPE_4__** inputs; TYPE_2__* priv; } ;
struct TYPE_16__ {int h; int w; int /*<<< orphan*/  time_base; void* sample_aspect_ratio; void* frame_rate; int /*<<< orphan*/  format; TYPE_5__* src; } ;
struct TYPE_15__ {int sync; void* after; void* before; int /*<<< orphan*/  time_base; } ;
struct TYPE_13__ {int depth; } ;
struct TYPE_12__ {int /*<<< orphan*/  log2_chroma_h; int /*<<< orphan*/  log2_chroma_w; TYPE_1__* comp; } ;
typedef  TYPE_3__ FFFrameSyncIn ;
typedef  void* AVRational ;
typedef  TYPE_4__ AVFilterLink ;
typedef  TYPE_5__ AVFilterContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_BUG ; 
 void* AV_CEIL_RSHIFT (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  EINVAL ; 
 void* EXT_STOP ; 
 int av_image_fill_linesizes (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  av_log (TYPE_5__*,int /*<<< orphan*/ ,char*,int,int,int,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  av_pix_fmt_count_planes (int /*<<< orphan*/ ) ; 
 TYPE_10__* av_pix_fmt_desc_get (int /*<<< orphan*/ ) ; 
 int ff_framesync_configure (TYPE_6__*) ; 
 int ff_framesync_init (TYPE_6__*,TYPE_5__*,int) ; 
 int /*<<< orphan*/  median_frames16 ; 
 int /*<<< orphan*/  median_frames8 ; 
 int /*<<< orphan*/  process_frame ; 

__attribute__((used)) static int config_output(AVFilterLink *outlink)
{
    AVFilterContext *ctx = outlink->src;
    XMedianContext *s = ctx->priv;
    AVRational frame_rate = ctx->inputs[0]->frame_rate;
    AVRational sar = ctx->inputs[0]->sample_aspect_ratio;
    AVFilterLink *inlink = ctx->inputs[0];
    int height = ctx->inputs[0]->h;
    int width = ctx->inputs[0]->w;
    FFFrameSyncIn *in;
    int i, ret;

    for (int i = 1; i < s->nb_inputs; i++) {
        if (ctx->inputs[i]->h != height || ctx->inputs[i]->w != width) {
            av_log(ctx, AV_LOG_ERROR, "Input %d size (%dx%d) does not match input %d size (%dx%d).\n", i, ctx->inputs[i]->w, ctx->inputs[i]->h, 0, width, height);
            return AVERROR(EINVAL);
        }
    }

    s->desc = av_pix_fmt_desc_get(outlink->format);
    if (!s->desc)
        return AVERROR_BUG;
    s->nb_planes = av_pix_fmt_count_planes(outlink->format);
    s->depth = s->desc->comp[0].depth;
    s->max = (1 << s->depth) - 1;

    if (s->depth <= 8)
        s->median_frames = median_frames8;
    else
        s->median_frames = median_frames16;

    if ((ret = av_image_fill_linesizes(s->linesize, inlink->format, inlink->w)) < 0)
        return ret;

    s->width[1] = s->width[2] = AV_CEIL_RSHIFT(inlink->w, s->desc->log2_chroma_w);
    s->width[0] = s->width[3] = inlink->w;
    s->height[1] = s->height[2] = AV_CEIL_RSHIFT(inlink->h, s->desc->log2_chroma_h);
    s->height[0] = s->height[3] = inlink->h;

    outlink->w          = width;
    outlink->h          = height;
    outlink->frame_rate = frame_rate;
    outlink->sample_aspect_ratio = sar;

    if ((ret = ff_framesync_init(&s->fs, ctx, s->nb_inputs)) < 0)
        return ret;

    in = s->fs.in;
    s->fs.opaque = s;
    s->fs.on_event = process_frame;

    for (i = 0; i < s->nb_inputs; i++) {
        AVFilterLink *inlink = ctx->inputs[i];

        in[i].time_base = inlink->time_base;
        in[i].sync   = 1;
        in[i].before = EXT_STOP;
        in[i].after  = EXT_STOP;
    }

    ret = ff_framesync_configure(&s->fs);
    outlink->time_base = s->fs.time_base;

    return ret;
}