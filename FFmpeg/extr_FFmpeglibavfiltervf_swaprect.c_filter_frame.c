#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;
typedef  struct TYPE_12__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_17__ {TYPE_2__* priv; TYPE_4__** outputs; } ;
struct TYPE_12__ {scalar_t__ num; } ;
struct TYPE_16__ {double w; double h; double frame_count_out; TYPE_10__ time_base; TYPE_10__ sample_aspect_ratio; TYPE_5__* dst; } ;
struct TYPE_15__ {int pts; double pkt_pos; int* linesize; int /*<<< orphan*/ ** data; } ;
struct TYPE_14__ {int nb_planes; int* pixsteps; int /*<<< orphan*/ * temp; TYPE_1__* desc; int /*<<< orphan*/  y2; int /*<<< orphan*/  x2; int /*<<< orphan*/  y1; int /*<<< orphan*/  x1; int /*<<< orphan*/  h; int /*<<< orphan*/  w; } ;
struct TYPE_13__ {int /*<<< orphan*/  log2_chroma_h; int /*<<< orphan*/  log2_chroma_w; } ;
typedef  TYPE_2__ SwapRectContext ;
typedef  TYPE_3__ AVFrame ;
typedef  TYPE_4__ AVFilterLink ;
typedef  TYPE_5__ AVFilterContext ;

/* Variables and functions */
 int AV_CEIL_RSHIFT (int,int /*<<< orphan*/ ) ; 
 int AV_NOPTS_VALUE ; 
 int FFMIN3 (int,int,int) ; 
 int NAN ; 
 size_t VAR_A ; 
 size_t VAR_DAR ; 
 size_t VAR_H ; 
 size_t VAR_N ; 
 size_t VAR_POS ; 
 size_t VAR_SAR ; 
 size_t VAR_T ; 
 int VAR_VARS_NB ; 
 size_t VAR_W ; 
 int av_clip (int,int /*<<< orphan*/ ,int) ; 
 int av_expr_parse_and_eval (double*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,double*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_5__*) ; 
 int av_q2d (TYPE_10__) ; 
 int ff_filter_frame (TYPE_4__*,TYPE_3__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  var_names ; 

__attribute__((used)) static int filter_frame(AVFilterLink *inlink, AVFrame *in)
{
    AVFilterContext *ctx = inlink->dst;
    AVFilterLink *outlink = ctx->outputs[0];
    SwapRectContext *s = ctx->priv;
    double var_values[VAR_VARS_NB];
    int x1[4], y1[4];
    int x2[4], y2[4];
    int aw[4], ah[4];
    int lw[4], lh[4];
    int pw[4], ph[4];
    double dw,  dh;
    double dx1, dy1;
    double dx2, dy2;
    int y, p, w, h, ret;

    var_values[VAR_W]   = inlink->w;
    var_values[VAR_H]   = inlink->h;
    var_values[VAR_A]   = (float) inlink->w / inlink->h;
    var_values[VAR_SAR] = inlink->sample_aspect_ratio.num ? av_q2d(inlink->sample_aspect_ratio) : 1;
    var_values[VAR_DAR] = var_values[VAR_A] * var_values[VAR_SAR];
    var_values[VAR_N]   = inlink->frame_count_out;
    var_values[VAR_T]   = in->pts == AV_NOPTS_VALUE ? NAN : in->pts * av_q2d(inlink->time_base);
    var_values[VAR_POS] = in->pkt_pos ? NAN : in->pkt_pos;

    ret = av_expr_parse_and_eval(&dw, s->w,
                                 var_names, &var_values[0],
                                 NULL, NULL, NULL, NULL,
                                 0, 0, ctx);
    if (ret < 0)
        return ret;

    ret = av_expr_parse_and_eval(&dh, s->h,
                                 var_names, &var_values[0],
                                 NULL, NULL, NULL, NULL,
                                 0, 0, ctx);
    if (ret < 0)
        return ret;

    ret = av_expr_parse_and_eval(&dx1, s->x1,
                                 var_names, &var_values[0],
                                 NULL, NULL, NULL, NULL,
                                 0, 0, ctx);
    if (ret < 0)
        return ret;

    ret = av_expr_parse_and_eval(&dy1, s->y1,
                                 var_names, &var_values[0],
                                 NULL, NULL, NULL, NULL,
                                 0, 0, ctx);
    if (ret < 0)
        return ret;

    ret = av_expr_parse_and_eval(&dx2, s->x2,
                                 var_names, &var_values[0],
                                 NULL, NULL, NULL, NULL,
                                 0, 0, ctx);
    if (ret < 0)
        return ret;

    ret = av_expr_parse_and_eval(&dy2, s->y2,
                                 var_names, &var_values[0],
                                 NULL, NULL, NULL, NULL,
                                 0, 0, ctx);
    if (ret < 0)
        return ret;

    w = dw; h = dh; x1[0] = dx1; y1[0] = dy1; x2[0] = dx2; y2[0] = dy2;

    x1[0] = av_clip(x1[0], 0, inlink->w - 1);
    y1[0] = av_clip(y1[0], 0, inlink->w - 1);

    x2[0] = av_clip(x2[0], 0, inlink->w - 1);
    y2[0] = av_clip(y2[0], 0, inlink->w - 1);

    ah[1] = ah[2] = AV_CEIL_RSHIFT(h, s->desc->log2_chroma_h);
    ah[0] = ah[3] = h;
    aw[1] = aw[2] = AV_CEIL_RSHIFT(w, s->desc->log2_chroma_w);
    aw[0] = aw[3] = w;

    w = FFMIN3(w, inlink->w - x1[0], inlink->w - x2[0]);
    h = FFMIN3(h, inlink->h - y1[0], inlink->h - y2[0]);

    ph[1] = ph[2] = AV_CEIL_RSHIFT(h, s->desc->log2_chroma_h);
    ph[0] = ph[3] = h;
    pw[1] = pw[2] = AV_CEIL_RSHIFT(w, s->desc->log2_chroma_w);
    pw[0] = pw[3] = w;

    lh[1] = lh[2] = AV_CEIL_RSHIFT(inlink->h, s->desc->log2_chroma_h);
    lh[0] = lh[3] = inlink->h;
    lw[1] = lw[2] = AV_CEIL_RSHIFT(inlink->w, s->desc->log2_chroma_w);
    lw[0] = lw[3] = inlink->w;

    x1[1] = x1[2] = AV_CEIL_RSHIFT(x1[0], s->desc->log2_chroma_w);
    x1[0] = x1[3] = x1[0];
    y1[1] = y1[2] = AV_CEIL_RSHIFT(y1[0], s->desc->log2_chroma_h);
    y1[0] = y1[3] = y1[0];

    x2[1] = x2[2] = AV_CEIL_RSHIFT(x2[0], s->desc->log2_chroma_w);
    x2[0] = x2[3] = x2[0];
    y2[1] = y2[2] = AV_CEIL_RSHIFT(y2[0], s->desc->log2_chroma_h);
    y2[0] = y2[3] = y2[0];

    for (p = 0; p < s->nb_planes; p++) {
        if (ph[p] == ah[p] && pw[p] == aw[p]) {
            uint8_t *src = in->data[p] + y1[p] * in->linesize[p] + x1[p] * s->pixsteps[p];
            uint8_t *dst = in->data[p] + y2[p] * in->linesize[p] + x2[p] * s->pixsteps[p];

            for (y = 0; y < ph[p]; y++) {
                memcpy(s->temp, src, pw[p] * s->pixsteps[p]);
                memmove(src, dst, pw[p] * s->pixsteps[p]);
                memcpy(dst, s->temp, pw[p] * s->pixsteps[p]);
                src += in->linesize[p];
                dst += in->linesize[p];
            }
        }
    }

    return ff_filter_frame(outlink, in);
}