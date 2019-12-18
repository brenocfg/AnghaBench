#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {scalar_t__ num; } ;
struct TYPE_13__ {TYPE_1__* priv; } ;
struct TYPE_12__ {double h; double w; TYPE_6__ sample_aspect_ratio; int /*<<< orphan*/  format; TYPE_4__* dst; } ;
struct TYPE_11__ {double log2_chroma_w; double log2_chroma_h; int flags; } ;
struct TYPE_10__ {double hsub; double vsub; int have_alpha; char* x_expr; double x; char* y_expr; double y; char* w_expr; double w; char* h_expr; double h; char* t_expr; double thickness; int /*<<< orphan*/ * yuv_color; } ;
typedef  TYPE_1__ DrawBoxContext ;
typedef  TYPE_2__ AVPixFmtDescriptor ;
typedef  TYPE_3__ AVFilterLink ;
typedef  TYPE_4__ AVFilterContext ;

/* Variables and functions */
 size_t A ; 
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_LOG_VERBOSE ; 
 int AV_PIX_FMT_FLAG_ALPHA ; 
 int /*<<< orphan*/  EINVAL ; 
 double INT_MAX ; 
 double NAN ; 
 int NUM_EXPR_EVALS ; 
 size_t U ; 
 size_t V ; 
 int VARS_NB ; 
 size_t VAR_DAR ; 
 size_t VAR_H ; 
 size_t VAR_HSUB ; 
 size_t VAR_IH ; 
 size_t VAR_IN_H ; 
 size_t VAR_IN_W ; 
 size_t VAR_IW ; 
 size_t VAR_MAX ; 
 size_t VAR_SAR ; 
 size_t VAR_T ; 
 size_t VAR_VSUB ; 
 size_t VAR_W ; 
 size_t VAR_X ; 
 size_t VAR_Y ; 
 size_t Y ; 
 int av_expr_parse_and_eval (double*,char*,int /*<<< orphan*/ ,double*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  av_log (TYPE_4__*,int /*<<< orphan*/ ,char*,...) ; 
 TYPE_2__* av_pix_fmt_desc_get (int /*<<< orphan*/ ) ; 
 int av_q2d (TYPE_6__) ; 
 int /*<<< orphan*/  var_names ; 

__attribute__((used)) static int config_input(AVFilterLink *inlink)
{
    AVFilterContext *ctx = inlink->dst;
    DrawBoxContext *s = ctx->priv;
    const AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(inlink->format);
    double var_values[VARS_NB], res;
    char *expr;
    int ret;
    int i;

    s->hsub = desc->log2_chroma_w;
    s->vsub = desc->log2_chroma_h;
    s->have_alpha = desc->flags & AV_PIX_FMT_FLAG_ALPHA;

    var_values[VAR_IN_H] = var_values[VAR_IH] = inlink->h;
    var_values[VAR_IN_W] = var_values[VAR_IW] = inlink->w;
    var_values[VAR_SAR]  = inlink->sample_aspect_ratio.num ? av_q2d(inlink->sample_aspect_ratio) : 1;
    var_values[VAR_DAR]  = (double)inlink->w / inlink->h * var_values[VAR_SAR];
    var_values[VAR_HSUB] = s->hsub;
    var_values[VAR_VSUB] = s->vsub;
    var_values[VAR_X] = NAN;
    var_values[VAR_Y] = NAN;
    var_values[VAR_H] = NAN;
    var_values[VAR_W] = NAN;
    var_values[VAR_T] = NAN;

    for (i = 0; i <= NUM_EXPR_EVALS; i++) {
        /* evaluate expressions, fail on last iteration */
        var_values[VAR_MAX] = inlink->w;
        if ((ret = av_expr_parse_and_eval(&res, (expr = s->x_expr),
                                          var_names, var_values,
                                          NULL, NULL, NULL, NULL, NULL, 0, ctx)) < 0 && i == NUM_EXPR_EVALS)
            goto fail;
        s->x = var_values[VAR_X] = res;

        var_values[VAR_MAX] = inlink->h;
        if ((ret = av_expr_parse_and_eval(&res, (expr = s->y_expr),
                                          var_names, var_values,
                                          NULL, NULL, NULL, NULL, NULL, 0, ctx)) < 0 && i == NUM_EXPR_EVALS)
            goto fail;
        s->y = var_values[VAR_Y] = res;

        var_values[VAR_MAX] = inlink->w - s->x;
        if ((ret = av_expr_parse_and_eval(&res, (expr = s->w_expr),
                                          var_names, var_values,
                                          NULL, NULL, NULL, NULL, NULL, 0, ctx)) < 0 && i == NUM_EXPR_EVALS)
            goto fail;
        s->w = var_values[VAR_W] = res;

        var_values[VAR_MAX] = inlink->h - s->y;
        if ((ret = av_expr_parse_and_eval(&res, (expr = s->h_expr),
                                          var_names, var_values,
                                          NULL, NULL, NULL, NULL, NULL, 0, ctx)) < 0 && i == NUM_EXPR_EVALS)
            goto fail;
        s->h = var_values[VAR_H] = res;

        var_values[VAR_MAX] = INT_MAX;
        if ((ret = av_expr_parse_and_eval(&res, (expr = s->t_expr),
                                          var_names, var_values,
                                          NULL, NULL, NULL, NULL, NULL, 0, ctx)) < 0 && i == NUM_EXPR_EVALS)
            goto fail;
        s->thickness = var_values[VAR_T] = res;
    }

    /* if w or h are zero, use the input w/h */
    s->w = (s->w > 0) ? s->w : inlink->w;
    s->h = (s->h > 0) ? s->h : inlink->h;

    /* sanity check width and height */
    if (s->w <  0 || s->h <  0) {
        av_log(ctx, AV_LOG_ERROR, "Size values less than 0 are not acceptable.\n");
        return AVERROR(EINVAL);
    }

    av_log(ctx, AV_LOG_VERBOSE, "x:%d y:%d w:%d h:%d color:0x%02X%02X%02X%02X\n",
           s->x, s->y, s->w, s->h,
           s->yuv_color[Y], s->yuv_color[U], s->yuv_color[V], s->yuv_color[A]);

    return 0;

fail:
    av_log(ctx, AV_LOG_ERROR,
           "Error when evaluating the expression '%s'.\n",
           expr);
    return ret;
}