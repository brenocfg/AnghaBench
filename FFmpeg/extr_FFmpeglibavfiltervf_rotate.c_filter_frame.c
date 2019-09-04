#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_6__ ;
typedef  struct TYPE_25__   TYPE_5__ ;
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;

/* Type definitions */
struct TYPE_22__ {int inw; int inh; int const outh; int const outw; int const xi; int const yi; int const xprime; int const yprime; int plane; int c; int s; TYPE_4__* out; TYPE_4__* in; } ;
typedef  TYPE_2__ ThreadData ;
struct TYPE_26__ {TYPE_1__* internal; TYPE_3__* priv; TYPE_5__** outputs; } ;
struct TYPE_25__ {int /*<<< orphan*/  h; int /*<<< orphan*/  w; int /*<<< orphan*/  time_base; int /*<<< orphan*/  frame_count_out; TYPE_6__* dst; } ;
struct TYPE_24__ {int /*<<< orphan*/  linesize; int /*<<< orphan*/  data; int /*<<< orphan*/  pts; } ;
struct TYPE_23__ {double angle; int nb_planes; int hsub; int vsub; int /*<<< orphan*/  color; int /*<<< orphan*/  draw; scalar_t__ fillcolor_enable; int /*<<< orphan*/ * var_values; int /*<<< orphan*/  angle_expr; } ;
struct TYPE_21__ {int /*<<< orphan*/  (* execute ) (TYPE_6__*,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_3__ RotContext ;
typedef  TYPE_4__ AVFrame ;
typedef  TYPE_5__ AVFilterLink ;
typedef  TYPE_6__ AVFilterContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AV_CEIL_RSHIFT (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  AV_LOG_DEBUG ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  FFMIN (int const,int /*<<< orphan*/ ) ; 
 double FIXP ; 
 int INT_PI ; 
 int M_PI ; 
 int /*<<< orphan*/  TS2T (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t VAR_N ; 
 size_t VAR_T ; 
 double av_expr_eval (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  av_frame_copy_props (TYPE_4__*,TYPE_4__*) ; 
 int /*<<< orphan*/  av_frame_free (TYPE_4__**) ; 
 int /*<<< orphan*/  av_log (TYPE_6__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ff_fill_rectangle (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ff_filter_frame (TYPE_5__*,TYPE_4__*) ; 
 int /*<<< orphan*/  ff_filter_get_nb_threads (TYPE_6__*) ; 
 TYPE_4__* ff_get_video_buffer (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  filter_slice ; 
 int int_sin (int) ; 
 int /*<<< orphan*/  stub1 (TYPE_6__*,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int filter_frame(AVFilterLink *inlink, AVFrame *in)
{
    AVFilterContext *ctx = inlink->dst;
    AVFilterLink *outlink = ctx->outputs[0];
    AVFrame *out;
    RotContext *rot = ctx->priv;
    int angle_int, s, c, plane;
    double res;

    out = ff_get_video_buffer(outlink, outlink->w, outlink->h);
    if (!out) {
        av_frame_free(&in);
        return AVERROR(ENOMEM);
    }
    av_frame_copy_props(out, in);

    rot->var_values[VAR_N] = inlink->frame_count_out;
    rot->var_values[VAR_T] = TS2T(in->pts, inlink->time_base);
    rot->angle = res = av_expr_eval(rot->angle_expr, rot->var_values, rot);

    av_log(ctx, AV_LOG_DEBUG, "n:%f time:%f angle:%f/PI\n",
           rot->var_values[VAR_N], rot->var_values[VAR_T], rot->angle/M_PI);

    angle_int = res * FIXP * 16;
    s = int_sin(angle_int);
    c = int_sin(angle_int + INT_PI/2);

    /* fill background */
    if (rot->fillcolor_enable)
        ff_fill_rectangle(&rot->draw, &rot->color, out->data, out->linesize,
                          0, 0, outlink->w, outlink->h);

    for (plane = 0; plane < rot->nb_planes; plane++) {
        int hsub = plane == 1 || plane == 2 ? rot->hsub : 0;
        int vsub = plane == 1 || plane == 2 ? rot->vsub : 0;
        const int outw = AV_CEIL_RSHIFT(outlink->w, hsub);
        const int outh = AV_CEIL_RSHIFT(outlink->h, vsub);
        ThreadData td = { .in = in,   .out  = out,
                          .inw  = AV_CEIL_RSHIFT(inlink->w, hsub),
                          .inh  = AV_CEIL_RSHIFT(inlink->h, vsub),
                          .outh = outh, .outw = outw,
                          .xi = -(outw-1) * c / 2, .yi =  (outw-1) * s / 2,
                          .xprime = -(outh-1) * s / 2,
                          .yprime = -(outh-1) * c / 2,
                          .plane = plane, .c = c, .s = s };


        ctx->internal->execute(ctx, filter_slice, &td, NULL, FFMIN(outh, ff_filter_get_nb_threads(ctx)));
    }

    av_frame_free(&in);
    return ff_filter_frame(outlink, out);
}