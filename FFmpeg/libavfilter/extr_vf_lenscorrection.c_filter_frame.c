#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int int64_t ;
struct TYPE_13__ {int w; int h; int xcenter; int ycenter; int plane; int* correction; int /*<<< orphan*/ * out; int /*<<< orphan*/ * in; } ;
typedef  TYPE_2__ ThreadData ;
struct TYPE_16__ {TYPE_1__* internal; scalar_t__ priv; TYPE_4__** outputs; } ;
struct TYPE_15__ {int /*<<< orphan*/  h; int /*<<< orphan*/  w; TYPE_5__* dst; } ;
struct TYPE_14__ {int nb_planes; int hsub; int vsub; int cx; int cy; int k1; int k2; int** correction; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct TYPE_12__ {int /*<<< orphan*/  (* execute ) (TYPE_5__*,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_3__ LenscorrectionCtx ;
typedef  int /*<<< orphan*/  AVFrame ;
typedef  TYPE_4__ AVFilterLink ;
typedef  TYPE_5__ AVFilterContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AV_CEIL_RSHIFT (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  FFMIN (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_frame_copy_props (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_frame_free (int /*<<< orphan*/ **) ; 
 int* av_malloc_array (int,int) ; 
 int ff_filter_frame (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ff_filter_get_nb_threads (TYPE_5__*) ; 
 int /*<<< orphan*/ * ff_get_video_buffer (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  filter_slice ; 
 int /*<<< orphan*/  stub1 (TYPE_5__*,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int filter_frame(AVFilterLink *inlink, AVFrame *in)
{
    AVFilterContext *ctx = inlink->dst;
    AVFilterLink *outlink = ctx->outputs[0];
    LenscorrectionCtx *rect = (LenscorrectionCtx*)ctx->priv;
    AVFrame *out = ff_get_video_buffer(outlink, outlink->w, outlink->h);
    int plane;

    if (!out) {
        av_frame_free(&in);
        return AVERROR(ENOMEM);
    }

    av_frame_copy_props(out, in);

    for (plane = 0; plane < rect->nb_planes; ++plane) {
        int hsub = plane == 1 || plane == 2 ? rect->hsub : 0;
        int vsub = plane == 1 || plane == 2 ? rect->vsub : 0;
        int w = AV_CEIL_RSHIFT(rect->width, hsub);
        int h = AV_CEIL_RSHIFT(rect->height, vsub);
        int xcenter = rect->cx * w;
        int ycenter = rect->cy * h;
        int k1 = rect->k1 * (1<<24);
        int k2 = rect->k2 * (1<<24);
        ThreadData td = {
            .in = in,
            .out  = out,
            .w  = w,
            .h  = h,
            .xcenter = xcenter,
            .ycenter = ycenter,
            .plane = plane};

        if (!rect->correction[plane]) {
            int i,j;
            const int64_t r2inv = (4LL<<60) / (w * w + h * h);

            rect->correction[plane] = av_malloc_array(w, h * sizeof(**rect->correction));
            if (!rect->correction[plane])
                return AVERROR(ENOMEM);
            for (j = 0; j < h; j++) {
                const int off_y = j - ycenter;
                const int off_y2 = off_y * off_y;
                for (i = 0; i < w; i++) {
                    const int off_x = i - xcenter;
                    const int64_t r2 = ((off_x * off_x + off_y2) * r2inv + (1LL<<31)) >> 32;
                    const int64_t r4 = (r2 * r2 + (1<<27)) >> 28;
                    const int radius_mult = (r2 * k1 + r4 * k2 + (1LL<<27) + (1LL<<52))>>28;
                    rect->correction[plane][j * w + i] = radius_mult;
                }
            }
        }

        td.correction = rect->correction[plane];
        ctx->internal->execute(ctx, filter_slice, &td, NULL, FFMIN(h, ff_filter_get_nb_threads(ctx)));
    }

    av_frame_free(&in);
    return ff_filter_frame(outlink, out);
}