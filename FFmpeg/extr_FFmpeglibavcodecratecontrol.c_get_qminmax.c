#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int lmin; int lmax; TYPE_1__* avctx; } ;
struct TYPE_4__ {int /*<<< orphan*/  i_quant_offset; int /*<<< orphan*/  i_quant_factor; int /*<<< orphan*/  b_quant_offset; int /*<<< orphan*/  b_quant_factor; } ;
typedef  TYPE_2__ MpegEncContext ;

/* Variables and functions */
#define  AV_PICTURE_TYPE_B 129 
#define  AV_PICTURE_TYPE_I 128 
 int FFABS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FF_LAMBDA_MAX ; 
 int /*<<< orphan*/  av_assert0 (int) ; 
 int av_clip (int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void get_qminmax(int *qmin_ret, int *qmax_ret, MpegEncContext *s, int pict_type)
{
    int qmin = s->lmin;
    int qmax = s->lmax;

    av_assert0(qmin <= qmax);

    switch (pict_type) {
    case AV_PICTURE_TYPE_B:
        qmin = (int)(qmin * FFABS(s->avctx->b_quant_factor) + s->avctx->b_quant_offset + 0.5);
        qmax = (int)(qmax * FFABS(s->avctx->b_quant_factor) + s->avctx->b_quant_offset + 0.5);
        break;
    case AV_PICTURE_TYPE_I:
        qmin = (int)(qmin * FFABS(s->avctx->i_quant_factor) + s->avctx->i_quant_offset + 0.5);
        qmax = (int)(qmax * FFABS(s->avctx->i_quant_factor) + s->avctx->i_quant_offset + 0.5);
        break;
    }

    qmin = av_clip(qmin, 1, FF_LAMBDA_MAX);
    qmax = av_clip(qmax, 1, FF_LAMBDA_MAX);

    if (qmax < qmin)
        qmax = qmin;

    *qmin_ret = qmin;
    *qmax_ret = qmax;
}