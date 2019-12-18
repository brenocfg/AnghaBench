#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int8_t ;
struct TYPE_6__ {int /*<<< orphan*/ * qscale_table; } ;
struct TYPE_7__ {int mb_num; unsigned int* lambda_table; size_t* mb_index2xy; TYPE_1__* avctx; TYPE_2__ current_picture; } ;
struct TYPE_5__ {int /*<<< orphan*/  qmax; int /*<<< orphan*/  qmin; } ;
typedef  TYPE_3__ MpegEncContext ;

/* Variables and functions */
 int FF_LAMBDA_SCALE ; 
 int FF_LAMBDA_SHIFT ; 
 int /*<<< orphan*/  av_clip (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void ff_init_qscale_tab(MpegEncContext *s)
{
    int8_t * const qscale_table = s->current_picture.qscale_table;
    int i;

    for (i = 0; i < s->mb_num; i++) {
        unsigned int lam = s->lambda_table[s->mb_index2xy[i]];
        int qp = (lam * 139 + FF_LAMBDA_SCALE * 64) >> (FF_LAMBDA_SHIFT + 7);
        qscale_table[s->mb_index2xy[i]] = av_clip(qp, s->avctx->qmin,
                                                  s->avctx->qmax);
    }
}