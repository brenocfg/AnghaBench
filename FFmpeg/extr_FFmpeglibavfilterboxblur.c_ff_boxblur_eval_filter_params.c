#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int w; int h; int /*<<< orphan*/ * dst; int /*<<< orphan*/  format; } ;
struct TYPE_10__ {int log2_chroma_w; int log2_chroma_h; } ;
struct TYPE_9__ {char* radius_expr; scalar_t__ power; double radius; } ;
typedef  TYPE_1__ FilterParam ;
typedef  TYPE_2__ AVPixFmtDescriptor ;
typedef  TYPE_3__ AVFilterLink ;
typedef  int /*<<< orphan*/  AVFilterContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_LOG_VERBOSE ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 int FFMIN (int,int) ; 
 int VARS_NB ; 
 size_t VAR_CH ; 
 size_t VAR_CW ; 
 size_t VAR_H ; 
 size_t VAR_HSUB ; 
 size_t VAR_VSUB ; 
 size_t VAR_W ; 
 int av_expr_parse_and_eval (double*,char*,int /*<<< orphan*/ ,double*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,...) ; 
 TYPE_2__* av_pix_fmt_desc_get (int /*<<< orphan*/ ) ; 
 void* av_strdup (char*) ; 
 int /*<<< orphan*/  var_names ; 

int ff_boxblur_eval_filter_params(AVFilterLink *inlink,
                                  FilterParam *luma_param,
                                  FilterParam *chroma_param,
                                  FilterParam *alpha_param)
{
    const AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(inlink->format);
    AVFilterContext *ctx = inlink->dst;
    int w = inlink->w, h = inlink->h;
    int cw, ch;
    double var_values[VARS_NB], res;
    char *expr;
    int ret;

    if (!luma_param->radius_expr) {
        av_log(ctx, AV_LOG_ERROR, "Luma radius expression is not set.\n");
        return AVERROR(EINVAL);
    }

    /* fill missing params */
    if (!chroma_param->radius_expr) {
        chroma_param->radius_expr = av_strdup(luma_param->radius_expr);
        if (!chroma_param->radius_expr)
            return AVERROR(ENOMEM);
    }
    if (chroma_param->power < 0)
        chroma_param->power = luma_param->power;

    if (!alpha_param->radius_expr) {
        alpha_param->radius_expr = av_strdup(luma_param->radius_expr);
        if (!alpha_param->radius_expr)
            return AVERROR(ENOMEM);
    }
    if (alpha_param->power < 0)
        alpha_param->power = luma_param->power;

    var_values[VAR_W]       = inlink->w;
    var_values[VAR_H]       = inlink->h;
    var_values[VAR_CW] = cw = w>>(desc->log2_chroma_w);
    var_values[VAR_CH] = ch = h>>(desc->log2_chroma_h);
    var_values[VAR_HSUB]    = 1<<(desc->log2_chroma_w);
    var_values[VAR_VSUB]    = 1<<(desc->log2_chroma_h);

#define EVAL_RADIUS_EXPR(comp)                                          \
    expr = comp->radius_expr;                                           \
    ret = av_expr_parse_and_eval(&res, expr, var_names, var_values,     \
                                 NULL, NULL, NULL, NULL, NULL, 0, ctx); \
    comp->radius = res;                                                 \
    if (ret < 0) {                                                      \
        av_log(NULL, AV_LOG_ERROR,                                      \
               "Error when evaluating " #comp " radius expression '%s'\n", expr); \
        return ret;                                                     \
    }

    EVAL_RADIUS_EXPR(luma_param);
    EVAL_RADIUS_EXPR(chroma_param);
    EVAL_RADIUS_EXPR(alpha_param);

    av_log(ctx, AV_LOG_VERBOSE,
           "luma_radius:%d luma_power:%d "
           "chroma_radius:%d chroma_power:%d "
           "alpha_radius:%d alpha_power:%d "
           "w:%d chroma_w:%d h:%d chroma_h:%d\n",
           luma_param  ->radius, luma_param  ->power,
           chroma_param->radius, chroma_param->power,
           alpha_param ->radius, alpha_param ->power,
           w, cw, h, ch);


#define CHECK_RADIUS_VAL(w_, h_, comp)                                  \
    if (comp->radius < 0 ||                                   \
        2*comp->radius > FFMIN(w_, h_)) {                     \
        av_log(ctx, AV_LOG_ERROR,                                       \
               "Invalid " #comp " radius value %d, must be >= 0 and <= %d\n", \
               comp->radius, FFMIN(w_, h_)/2);                \
        return AVERROR(EINVAL);                                         \
    }
    CHECK_RADIUS_VAL(w,  h,  luma_param);
    CHECK_RADIUS_VAL(cw, ch, chroma_param);
    CHECK_RADIUS_VAL(w,  h,  alpha_param);

    return 0;
}