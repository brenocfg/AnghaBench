#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_10__ {TYPE_1__* priv; } ;
struct TYPE_9__ {TYPE_3__* src; } ;
struct TYPE_8__ {int depth; int depthx; int depthy; int nb_planes; int nb_planesx; int odepth; double** lut; int* var_values; int /*<<< orphan*/ * comp_expr_str; int /*<<< orphan*/ ** comp_expr; void* lut2; } ;
typedef  TYPE_1__ LUT2Context ;
typedef  TYPE_2__ AVFilterLink ;
typedef  TYPE_3__ AVFilterContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 size_t VAR_X ; 
 size_t VAR_Y ; 
 double av_expr_eval (int /*<<< orphan*/ *,int*,TYPE_1__*) ; 
 int /*<<< orphan*/  av_expr_free (int /*<<< orphan*/ *) ; 
 int av_expr_parse (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  av_log (TYPE_3__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,...) ; 
 double* av_malloc_array (int,int) ; 
 scalar_t__ isnan (double) ; 
 void* lut2_16_16_16 ; 
 void* lut2_16_16_8 ; 
 void* lut2_16_8_16 ; 
 void* lut2_16_8_8 ; 
 void* lut2_8_16_16 ; 
 void* lut2_8_16_8 ; 
 void* lut2_8_8_16 ; 
 void* lut2_8_8_8 ; 
 int /*<<< orphan*/  var_names ; 

__attribute__((used)) static int config_output(AVFilterLink *outlink)
{
    AVFilterContext *ctx = outlink->src;
    LUT2Context *s = ctx->priv;
    int p, ret;

    s->depth = s->depthx + s->depthy;
    s->nb_planes = s->nb_planesx;

    s->lut2 = s->depth > 16 ? lut2_16_16_16 : lut2_8_8_8;
    if (s->odepth) {
        if (s->depthx == 8 && s->depthy == 8 && s->odepth > 8)
            s->lut2 = lut2_16_8_8;
        if (s->depthx > 8 && s->depthy == 8 && s->odepth > 8)
            s->lut2 = lut2_16_16_8;
        if (s->depthx == 8 && s->depthy > 8 && s->odepth > 8)
            s->lut2 = lut2_16_8_16;
        if (s->depthx == 8 && s->depthy == 8 && s->odepth == 8)
            s->lut2 = lut2_8_8_8;
        if (s->depthx > 8 && s->depthy == 8 && s->odepth == 8)
            s->lut2 = lut2_8_16_8;
        if (s->depthx == 8 && s->depthy > 8 && s->odepth == 8)
            s->lut2 = lut2_8_8_16;
        if (s->depthx > 8 && s->depthy > 8 && s->odepth == 8)
            s->lut2 = lut2_8_16_16;
    } else {
        s->odepth = s->depthx;
    }

    for (p = 0; p < s->nb_planes; p++) {
        s->lut[p] = av_malloc_array(1 << s->depth, sizeof(uint16_t));
        if (!s->lut[p])
            return AVERROR(ENOMEM);
    }

    for (p = 0; p < s->nb_planes; p++) {
        double res;
        int x, y;

        /* create the parsed expression */
        av_expr_free(s->comp_expr[p]);
        s->comp_expr[p] = NULL;
        ret = av_expr_parse(&s->comp_expr[p], s->comp_expr_str[p],
                            var_names, NULL, NULL, NULL, NULL, 0, ctx);
        if (ret < 0) {
            av_log(ctx, AV_LOG_ERROR,
                   "Error when parsing the expression '%s' for the component %d.\n",
                   s->comp_expr_str[p], p);
            return AVERROR(EINVAL);
        }

        /* compute the lut */
        for (y = 0; y < (1 << s->depthy); y++) {
            s->var_values[VAR_Y] = y;
            for (x = 0; x < (1 << s->depthx); x++) {
                s->var_values[VAR_X] = x;
                res = av_expr_eval(s->comp_expr[p], s->var_values, s);
                if (isnan(res)) {
                    av_log(ctx, AV_LOG_ERROR,
                           "Error when evaluating the expression '%s' for the values %d and %d for the component %d.\n",
                           s->comp_expr_str[p], x, y, p);
                    return AVERROR(EINVAL);
                }

                s->lut[p][(y << s->depthx) + x] = res;
            }
        }
    }

    return 0;
}