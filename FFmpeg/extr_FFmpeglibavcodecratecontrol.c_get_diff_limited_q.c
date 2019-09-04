#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {double i_quant_factor; double const i_quant_offset; double b_quant_factor; double const b_quant_offset; int max_qdiff; } ;
struct TYPE_8__ {double* last_qscale_for; size_t last_non_b_pict_type; } ;
struct TYPE_9__ {TYPE_4__* avctx; TYPE_2__ rc_context; } ;
struct TYPE_7__ {int new_pict_type; } ;
typedef  TYPE_1__ RateControlEntry ;
typedef  TYPE_2__ RateControlContext ;
typedef  TYPE_3__ MpegEncContext ;
typedef  TYPE_4__ AVCodecContext ;

/* Variables and functions */
 int const AV_PICTURE_TYPE_B ; 
 int const AV_PICTURE_TYPE_I ; 
 size_t AV_PICTURE_TYPE_P ; 
 double const FFABS (double) ; 
 int FF_QP2LAMBDA ; 

__attribute__((used)) static double get_diff_limited_q(MpegEncContext *s, RateControlEntry *rce, double q)
{
    RateControlContext *rcc   = &s->rc_context;
    AVCodecContext *a         = s->avctx;
    const int pict_type       = rce->new_pict_type;
    const double last_p_q     = rcc->last_qscale_for[AV_PICTURE_TYPE_P];
    const double last_non_b_q = rcc->last_qscale_for[rcc->last_non_b_pict_type];

    if (pict_type == AV_PICTURE_TYPE_I &&
        (a->i_quant_factor > 0.0 || rcc->last_non_b_pict_type == AV_PICTURE_TYPE_P))
        q = last_p_q * FFABS(a->i_quant_factor) + a->i_quant_offset;
    else if (pict_type == AV_PICTURE_TYPE_B &&
             a->b_quant_factor > 0.0)
        q = last_non_b_q * a->b_quant_factor + a->b_quant_offset;
    if (q < 1)
        q = 1;

    /* last qscale / qdiff stuff */
    if (rcc->last_non_b_pict_type == pict_type || pict_type != AV_PICTURE_TYPE_I) {
        double last_q     = rcc->last_qscale_for[pict_type];
        const int maxdiff = FF_QP2LAMBDA * a->max_qdiff;

        if (q > last_q + maxdiff)
            q = last_q + maxdiff;
        else if (q < last_q - maxdiff)
            q = last_q - maxdiff;
    }

    rcc->last_qscale_for[pict_type] = q; // Note we cannot do that after blurring

    if (pict_type != AV_PICTURE_TYPE_B)
        rcc->last_non_b_pict_type = pict_type;

    return q;
}