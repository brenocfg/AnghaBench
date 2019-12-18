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
struct TYPE_16__ {double qcompress; int rc_override_count; double i_quant_factor; double i_quant_offset; double b_quant_factor; double b_quant_offset; TYPE_1__* rc_override; } ;
struct TYPE_14__ {double* qscale_sum; double* i_cplx_sum; double* p_cplx_sum; double pass1_rc_eq_output_sum; int /*<<< orphan*/  rc_eq_eval; scalar_t__* frame_count; } ;
struct TYPE_15__ {double mb_num; TYPE_5__* avctx; int /*<<< orphan*/  rc_eq; TYPE_3__ rc_context; } ;
struct TYPE_13__ {int new_pict_type; double i_tex_bits; double qscale; double p_tex_bits; double const mv_bits; size_t pict_type; double f_code; double b_code; double const i_count; double const mc_mb_var_sum; double const mb_var_sum; } ;
struct TYPE_12__ {int start_frame; int end_frame; double quality_factor; scalar_t__ qscale; } ;
typedef  TYPE_1__ RcOverride ;
typedef  TYPE_2__ RateControlEntry ;
typedef  TYPE_3__ RateControlContext ;
typedef  TYPE_4__ MpegEncContext ;
typedef  TYPE_5__ AVCodecContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 size_t AV_PICTURE_TYPE_B ; 
 size_t AV_PICTURE_TYPE_I ; 
 size_t AV_PICTURE_TYPE_P ; 
 double M_E ; 
 double M_PI ; 
 double av_expr_eval (int /*<<< orphan*/ ,double*,TYPE_2__*) ; 
 int /*<<< orphan*/  av_log (TYPE_5__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 double bits2qp (TYPE_2__*,double) ; 
 scalar_t__ isnan (double) ; 
 double qp2bits (TYPE_2__*,scalar_t__) ; 

__attribute__((used)) static double get_qscale(MpegEncContext *s, RateControlEntry *rce,
                         double rate_factor, int frame_num)
{
    RateControlContext *rcc = &s->rc_context;
    AVCodecContext *a       = s->avctx;
    const int pict_type     = rce->new_pict_type;
    const double mb_num     = s->mb_num;
    double q, bits;
    int i;

    double const_values[] = {
        M_PI,
        M_E,
        rce->i_tex_bits * rce->qscale,
        rce->p_tex_bits * rce->qscale,
        (rce->i_tex_bits + rce->p_tex_bits) * (double)rce->qscale,
        rce->mv_bits / mb_num,
        rce->pict_type == AV_PICTURE_TYPE_B ? (rce->f_code + rce->b_code) * 0.5 : rce->f_code,
        rce->i_count / mb_num,
        rce->mc_mb_var_sum / mb_num,
        rce->mb_var_sum / mb_num,
        rce->pict_type == AV_PICTURE_TYPE_I,
        rce->pict_type == AV_PICTURE_TYPE_P,
        rce->pict_type == AV_PICTURE_TYPE_B,
        rcc->qscale_sum[pict_type] / (double)rcc->frame_count[pict_type],
        a->qcompress,
        rcc->i_cplx_sum[AV_PICTURE_TYPE_I] / (double)rcc->frame_count[AV_PICTURE_TYPE_I],
        rcc->i_cplx_sum[AV_PICTURE_TYPE_P] / (double)rcc->frame_count[AV_PICTURE_TYPE_P],
        rcc->p_cplx_sum[AV_PICTURE_TYPE_P] / (double)rcc->frame_count[AV_PICTURE_TYPE_P],
        rcc->p_cplx_sum[AV_PICTURE_TYPE_B] / (double)rcc->frame_count[AV_PICTURE_TYPE_B],
        (rcc->i_cplx_sum[pict_type] + rcc->p_cplx_sum[pict_type]) / (double)rcc->frame_count[pict_type],
        0
    };

    bits = av_expr_eval(rcc->rc_eq_eval, const_values, rce);
    if (isnan(bits)) {
        av_log(s->avctx, AV_LOG_ERROR, "Error evaluating rc_eq \"%s\"\n", s->rc_eq);
        return -1;
    }

    rcc->pass1_rc_eq_output_sum += bits;
    bits *= rate_factor;
    if (bits < 0.0)
        bits = 0.0;
    bits += 1.0; // avoid 1/0 issues

    /* user override */
    for (i = 0; i < s->avctx->rc_override_count; i++) {
        RcOverride *rco = s->avctx->rc_override;
        if (rco[i].start_frame > frame_num)
            continue;
        if (rco[i].end_frame < frame_num)
            continue;

        if (rco[i].qscale)
            bits = qp2bits(rce, rco[i].qscale);  // FIXME move at end to really force it?
        else
            bits *= rco[i].quality_factor;
    }

    q = bits2qp(rce, bits);

    /* I/B difference */
    if (pict_type == AV_PICTURE_TYPE_I && s->avctx->i_quant_factor < 0.0)
        q = -q * s->avctx->i_quant_factor + s->avctx->i_quant_offset;
    else if (pict_type == AV_PICTURE_TYPE_B && s->avctx->b_quant_factor < 0.0)
        q = -q * s->avctx->b_quant_factor + s->avctx->b_quant_offset;
    if (q < 1)
        q = 1;

    return q;
}