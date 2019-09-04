#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {double den; scalar_t__ num; } ;
struct TYPE_11__ {double w; double h; TYPE_2__ sample_aspect_ratio; int /*<<< orphan*/  format; TYPE_1__* src; } ;
struct TYPE_10__ {int log2_chroma_w; int log2_chroma_h; } ;
struct TYPE_8__ {int nb_inputs; TYPE_4__** inputs; } ;
typedef  TYPE_3__ AVPixFmtDescriptor ;
typedef  TYPE_4__ AVFilterLink ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 double M_E ; 
 double M_PHI ; 
 double M_PI ; 
 double NAN ; 
 size_t VARS_NB ; 
 int /*<<< orphan*/  VARS_S2R_NB ; 
 size_t VAR_A ; 
 size_t VAR_DAR ; 
 size_t VAR_E ; 
 size_t VAR_HSUB ; 
 size_t VAR_IH ; 
 size_t VAR_IN_H ; 
 size_t VAR_IN_W ; 
 size_t VAR_IW ; 
 size_t VAR_OH ; 
 size_t VAR_OHSUB ; 
 size_t VAR_OUT_H ; 
 size_t VAR_OUT_W ; 
 size_t VAR_OVSUB ; 
 size_t VAR_OW ; 
 size_t VAR_PHI ; 
 size_t VAR_PI ; 
 size_t VAR_S2R_MAIN_A ; 
 size_t VAR_S2R_MAIN_DAR ; 
 size_t VAR_S2R_MAIN_H ; 
 size_t VAR_S2R_MAIN_HSUB ; 
 size_t VAR_S2R_MAIN_SAR ; 
 size_t VAR_S2R_MAIN_VSUB ; 
 size_t VAR_S2R_MAIN_W ; 
 size_t VAR_S2R_MDAR ; 
 size_t VAR_SAR ; 
 size_t VAR_VSUB ; 
 int av_expr_parse_and_eval (double*,char const*,char const* const*,double*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  av_log (void*,int /*<<< orphan*/ ,char*,char const*,char const*,char const*) ; 
 TYPE_3__* av_pix_fmt_desc_get (int /*<<< orphan*/ ) ; 
 int av_rescale (int,int,int) ; 
 char** var_names ; 
 char** var_names_scale2ref ; 

int ff_scale_eval_dimensions(void *log_ctx,
    const char *w_expr, const char *h_expr,
    AVFilterLink *inlink, AVFilterLink *outlink,
    int *ret_w, int *ret_h)
{
    const AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(inlink->format);
    const AVPixFmtDescriptor *out_desc = av_pix_fmt_desc_get(outlink->format);
    const char *expr;
    int w, h;
    int factor_w, factor_h;
    int eval_w, eval_h;
    int ret;
    const char scale2ref = outlink->src->nb_inputs == 2 && outlink->src->inputs[1] == inlink;
    double var_values[VARS_NB + VARS_S2R_NB], res;
    const AVPixFmtDescriptor *main_desc;
    const AVFilterLink *main_link;
    const char *const *names = scale2ref ? var_names_scale2ref : var_names;

    if (scale2ref) {
        main_link = outlink->src->inputs[0];
        main_desc = av_pix_fmt_desc_get(main_link->format);
    }

    var_values[VAR_PI]    = M_PI;
    var_values[VAR_PHI]   = M_PHI;
    var_values[VAR_E]     = M_E;
    var_values[VAR_IN_W]  = var_values[VAR_IW] = inlink->w;
    var_values[VAR_IN_H]  = var_values[VAR_IH] = inlink->h;
    var_values[VAR_OUT_W] = var_values[VAR_OW] = NAN;
    var_values[VAR_OUT_H] = var_values[VAR_OH] = NAN;
    var_values[VAR_A]     = (double) inlink->w / inlink->h;
    var_values[VAR_SAR]   = inlink->sample_aspect_ratio.num ?
        (double) inlink->sample_aspect_ratio.num / inlink->sample_aspect_ratio.den : 1;
    var_values[VAR_DAR]   = var_values[VAR_A] * var_values[VAR_SAR];
    var_values[VAR_HSUB]  = 1 << desc->log2_chroma_w;
    var_values[VAR_VSUB]  = 1 << desc->log2_chroma_h;
    var_values[VAR_OHSUB] = 1 << out_desc->log2_chroma_w;
    var_values[VAR_OVSUB] = 1 << out_desc->log2_chroma_h;

    if (scale2ref) {
        var_values[VARS_NB + VAR_S2R_MAIN_W] = main_link->w;
        var_values[VARS_NB + VAR_S2R_MAIN_H] = main_link->h;
        var_values[VARS_NB + VAR_S2R_MAIN_A] = (double) main_link->w / main_link->h;
        var_values[VARS_NB + VAR_S2R_MAIN_SAR] = main_link->sample_aspect_ratio.num ?
            (double) main_link->sample_aspect_ratio.num / main_link->sample_aspect_ratio.den : 1;
        var_values[VARS_NB + VAR_S2R_MAIN_DAR] = var_values[VARS_NB + VAR_S2R_MDAR] =
            var_values[VARS_NB + VAR_S2R_MAIN_A] * var_values[VARS_NB + VAR_S2R_MAIN_SAR];
        var_values[VARS_NB + VAR_S2R_MAIN_HSUB] = 1 << main_desc->log2_chroma_w;
        var_values[VARS_NB + VAR_S2R_MAIN_VSUB] = 1 << main_desc->log2_chroma_h;
    }

    /* evaluate width and height */
    av_expr_parse_and_eval(&res, (expr = w_expr),
                           names, var_values,
                           NULL, NULL, NULL, NULL, NULL, 0, log_ctx);
    eval_w = var_values[VAR_OUT_W] = var_values[VAR_OW] = (int) res == 0 ? inlink->w : (int) res;

    if ((ret = av_expr_parse_and_eval(&res, (expr = h_expr),
                                      names, var_values,
                                      NULL, NULL, NULL, NULL, NULL, 0, log_ctx)) < 0)
        goto fail;
    eval_h = var_values[VAR_OUT_H] = var_values[VAR_OH] = (int) res == 0 ? inlink->h : (int) res;
    /* evaluate again the width, as it may depend on the output height */
    if ((ret = av_expr_parse_and_eval(&res, (expr = w_expr),
                                      names, var_values,
                                      NULL, NULL, NULL, NULL, NULL, 0, log_ctx)) < 0)
        goto fail;
    eval_w = (int) res == 0 ? inlink->w : (int) res;

    w = eval_w;
    h = eval_h;

    /* Check if it is requested that the result has to be divisible by a some
     * factor (w or h = -n with n being the factor). */
    factor_w = 1;
    factor_h = 1;
    if (w < -1) {
        factor_w = -w;
    }
    if (h < -1) {
        factor_h = -h;
    }

    if (w < 0 && h < 0) {
        w = inlink->w;
        h = inlink->h;
    }

    /* Make sure that the result is divisible by the factor we determined
     * earlier. If no factor was set, it is nothing will happen as the default
     * factor is 1 */
    if (w < 0)
        w = av_rescale(h, inlink->w, inlink->h * factor_w) * factor_w;
    if (h < 0)
        h = av_rescale(w, inlink->h, inlink->w * factor_h) * factor_h;

    *ret_w = w;
    *ret_h = h;

    return 0;

fail:
    av_log(log_ctx, AV_LOG_ERROR,
           "Error when evaluating the expression '%s'.\n"
           "Maybe the expression for out_w:'%s' or for out_h:'%s' is self-referencing.\n",
           expr, w_expr, h_expr);
    return ret;
}