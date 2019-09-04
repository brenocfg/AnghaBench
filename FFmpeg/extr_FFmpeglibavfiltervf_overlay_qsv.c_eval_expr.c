#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__* priv; } ;
struct TYPE_6__ {double* var_values; int /*<<< orphan*/  overlay_oh; int /*<<< orphan*/  overlay_ow; int /*<<< orphan*/  overlay_oy; int /*<<< orphan*/  overlay_ox; } ;
typedef  TYPE_1__ QSVOverlayContext ;
typedef  TYPE_2__ AVFilterContext ;
typedef  int /*<<< orphan*/  AVExpr ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 size_t VAR_OH ; 
 size_t VAR_OVERLAY_H ; 
 size_t VAR_OVERLAY_W ; 
 size_t VAR_OVERLAY_X ; 
 size_t VAR_OVERLAY_Y ; 
 size_t VAR_OW ; 
 size_t VAR_OX ; 
 size_t VAR_OY ; 
 double av_expr_eval (int /*<<< orphan*/ *,double*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_expr_free (int /*<<< orphan*/ *) ; 
 int av_expr_parse (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  av_log (TYPE_2__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  var_names ; 

__attribute__((used)) static int eval_expr(AVFilterContext *ctx)
{
    QSVOverlayContext *vpp = ctx->priv;
    double     *var_values = vpp->var_values;
    int                ret = 0;
    AVExpr *ox_expr = NULL, *oy_expr = NULL;
    AVExpr *ow_expr = NULL, *oh_expr = NULL;

#define PASS_EXPR(e, s) {\
    ret = av_expr_parse(&e, s, var_names, NULL, NULL, NULL, NULL, 0, ctx); \
    if (ret < 0) {\
        av_log(ctx, AV_LOG_ERROR, "Error when passing '%s'.\n", s);\
        goto release;\
    }\
}
    PASS_EXPR(ox_expr, vpp->overlay_ox);
    PASS_EXPR(oy_expr, vpp->overlay_oy);
    PASS_EXPR(ow_expr, vpp->overlay_ow);
    PASS_EXPR(oh_expr, vpp->overlay_oh);
#undef PASS_EXPR

    var_values[VAR_OVERLAY_W] =
    var_values[VAR_OW]        = av_expr_eval(ow_expr, var_values, NULL);
    var_values[VAR_OVERLAY_H] =
    var_values[VAR_OH]        = av_expr_eval(oh_expr, var_values, NULL);

    /* calc again in case ow is relative to oh */
    var_values[VAR_OVERLAY_W] =
    var_values[VAR_OW]        = av_expr_eval(ow_expr, var_values, NULL);

    var_values[VAR_OVERLAY_X] =
    var_values[VAR_OX]        = av_expr_eval(ox_expr, var_values, NULL);
    var_values[VAR_OVERLAY_Y] =
    var_values[VAR_OY]        = av_expr_eval(oy_expr, var_values, NULL);

    /* calc again in case ox is relative to oy */
    var_values[VAR_OVERLAY_X] =
    var_values[VAR_OX]        = av_expr_eval(ox_expr, var_values, NULL);

    /* calc overlay_w and overlay_h again incase relative to ox,oy */
    var_values[VAR_OVERLAY_W] =
    var_values[VAR_OW]        = av_expr_eval(ow_expr, var_values, NULL);
    var_values[VAR_OVERLAY_H] =
    var_values[VAR_OH]        = av_expr_eval(oh_expr, var_values, NULL);
    var_values[VAR_OVERLAY_W] =
    var_values[VAR_OW]        = av_expr_eval(ow_expr, var_values, NULL);

release:
    av_expr_free(ox_expr);
    av_expr_free(oy_expr);
    av_expr_free(ow_expr);
    av_expr_free(oh_expr);

    return ret;
}