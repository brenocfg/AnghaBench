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
struct TYPE_17__ {TYPE_4__** inputs; TYPE_2__* priv; } ;
struct TYPE_16__ {int h; int w; int /*<<< orphan*/  time_base; void* sample_aspect_ratio; void* frame_rate; int /*<<< orphan*/  format; TYPE_5__* src; } ;
struct TYPE_15__ {int sync; void* after; void* before; int /*<<< orphan*/  time_base; } ;
struct TYPE_14__ {int nb_inputs; char* layout; TYPE_6__ fs; scalar_t__ shortest; int /*<<< orphan*/  nb_planes; TYPE_10__* desc; TYPE_1__* items; scalar_t__ is_horizontal; scalar_t__ is_vertical; } ;
struct TYPE_13__ {int* height; int* y; int /*<<< orphan*/  x; int /*<<< orphan*/  linesize; } ;
struct TYPE_12__ {int /*<<< orphan*/  log2_chroma_h; } ;
typedef  TYPE_1__ StackItem ;
typedef  TYPE_2__ StackContext ;
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
 void* EXT_INFINITY ; 
 void* EXT_STOP ; 
 int FFMAX (int,int) ; 
 int av_image_fill_linesizes (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  av_log (TYPE_5__*,int /*<<< orphan*/ ,char*,int,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  av_pix_fmt_count_planes (int /*<<< orphan*/ ) ; 
 TYPE_10__* av_pix_fmt_desc_get (int /*<<< orphan*/ ) ; 
 char* av_strtok (char*,char*,char**) ; 
 int ff_framesync_configure (TYPE_6__*) ; 
 int ff_framesync_init (TYPE_6__*,TYPE_5__*,int) ; 
 int /*<<< orphan*/  process_frame ; 
 int sscanf (char*,char*,int*) ; 

__attribute__((used)) static int config_output(AVFilterLink *outlink)
{
    AVFilterContext *ctx = outlink->src;
    StackContext *s = ctx->priv;
    AVRational frame_rate = ctx->inputs[0]->frame_rate;
    AVRational sar = ctx->inputs[0]->sample_aspect_ratio;
    int height = ctx->inputs[0]->h;
    int width = ctx->inputs[0]->w;
    FFFrameSyncIn *in;
    int i, ret;

    s->desc = av_pix_fmt_desc_get(outlink->format);
    if (!s->desc)
        return AVERROR_BUG;

    if (s->is_vertical) {
        for (i = 0; i < s->nb_inputs; i++) {
            AVFilterLink *inlink = ctx->inputs[i];
            StackItem *item = &s->items[i];

            if (ctx->inputs[i]->w != width) {
                av_log(ctx, AV_LOG_ERROR, "Input %d width %d does not match input %d width %d.\n", i, ctx->inputs[i]->w, 0, width);
                return AVERROR(EINVAL);
            }

            if ((ret = av_image_fill_linesizes(item->linesize, inlink->format, inlink->w)) < 0) {
                return ret;
            }

            item->height[1] = item->height[2] = AV_CEIL_RSHIFT(inlink->h, s->desc->log2_chroma_h);
            item->height[0] = item->height[3] = inlink->h;

            if (i) {
                item->y[1] = item->y[2] = AV_CEIL_RSHIFT(height, s->desc->log2_chroma_h);
                item->y[0] = item->y[3] = height;

                height += ctx->inputs[i]->h;
            }
        }
    } else if (s->is_horizontal) {
        for (i = 0; i < s->nb_inputs; i++) {
            AVFilterLink *inlink = ctx->inputs[i];
            StackItem *item = &s->items[i];

            if (ctx->inputs[i]->h != height) {
                av_log(ctx, AV_LOG_ERROR, "Input %d height %d does not match input %d height %d.\n", i, ctx->inputs[i]->h, 0, height);
                return AVERROR(EINVAL);
            }

            if ((ret = av_image_fill_linesizes(item->linesize, inlink->format, inlink->w)) < 0) {
                return ret;
            }

            item->height[1] = item->height[2] = AV_CEIL_RSHIFT(inlink->h, s->desc->log2_chroma_h);
            item->height[0] = item->height[3] = inlink->h;

            if (i) {
                if ((ret = av_image_fill_linesizes(item->x, inlink->format, width)) < 0) {
                    return ret;
                }

                width += ctx->inputs[i]->w;
            }
        }
    } else {
        char *arg, *p = s->layout, *saveptr = NULL;
        char *arg2, *p2, *saveptr2 = NULL;
        char *arg3, *p3, *saveptr3 = NULL;
        int inw, inh, size;

        for (i = 0; i < s->nb_inputs; i++) {
            AVFilterLink *inlink = ctx->inputs[i];
            StackItem *item = &s->items[i];

            if (!(arg = av_strtok(p, "|", &saveptr)))
                return AVERROR(EINVAL);

            p = NULL;

            if ((ret = av_image_fill_linesizes(item->linesize, inlink->format, inlink->w)) < 0) {
                return ret;
            }

            item->height[1] = item->height[2] = AV_CEIL_RSHIFT(inlink->h, s->desc->log2_chroma_h);
            item->height[0] = item->height[3] = inlink->h;

            p2 = arg;
            inw = inh = 0;

            for (int j = 0; j < 2; j++) {
                if (!(arg2 = av_strtok(p2, "_", &saveptr2)))
                    return AVERROR(EINVAL);

                p2 = NULL;
                p3 = arg2;
                while ((arg3 = av_strtok(p3, "+", &saveptr3))) {
                    p3 = NULL;
                    if (sscanf(arg3, "w%d", &size) == 1) {
                        if (size == i || size < 0 || size >= s->nb_inputs)
                            return AVERROR(EINVAL);

                        if (!j)
                            inw += ctx->inputs[size]->w;
                        else
                            inh += ctx->inputs[size]->w;
                    } else if (sscanf(arg3, "h%d", &size) == 1) {
                        if (size == i || size < 0 || size >= s->nb_inputs)
                            return AVERROR(EINVAL);

                        if (!j)
                            inw += ctx->inputs[size]->h;
                        else
                            inh += ctx->inputs[size]->h;
                    } else if (sscanf(arg3, "%d", &size) == 1) {
                        if (size < 0)
                            return AVERROR(EINVAL);

                        if (!j)
                            inw += size;
                        else
                            inh += size;
                    } else {
                        return AVERROR(EINVAL);
                    }
                }
            }

            if ((ret = av_image_fill_linesizes(item->x, inlink->format, inw)) < 0) {
                return ret;
            }

            item->y[1] = item->y[2] = AV_CEIL_RSHIFT(inh, s->desc->log2_chroma_h);
            item->y[0] = item->y[3] = inh;

            width  = FFMAX(width,  inlink->w + inw);
            height = FFMAX(height, inlink->h + inh);
        }
    }

    s->nb_planes = av_pix_fmt_count_planes(outlink->format);

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
        in[i].after  = s->shortest ? EXT_STOP : EXT_INFINITY;
    }

    ret = ff_framesync_configure(&s->fs);
    outlink->time_base = s->fs.time_base;

    return ret;
}