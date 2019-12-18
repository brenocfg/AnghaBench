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
struct TYPE_5__ {int q_scale_type; int lambda; int qscale; int lambda2; TYPE_1__* avctx; scalar_t__ vbv_ignore_qmax; } ;
struct TYPE_4__ {int qmin; int qmax; } ;
typedef  TYPE_2__ MpegEncContext ;

/* Variables and functions */
 int FFABS (int) ; 
 int FF_ARRAY_ELEMS (int*) ; 
 int FF_LAMBDA_SCALE ; 
 int FF_LAMBDA_SHIFT ; 
 int INT_MAX ; 
 int av_clip (int,int,int) ; 
 int* ff_mpeg2_non_linear_qscale ; 

__attribute__((used)) static inline void update_qscale(MpegEncContext *s)
{
    if (s->q_scale_type == 1 && 0) {
        int i;
        int bestdiff=INT_MAX;
        int best = 1;

        for (i = 0 ; i<FF_ARRAY_ELEMS(ff_mpeg2_non_linear_qscale); i++) {
            int diff = FFABS((ff_mpeg2_non_linear_qscale[i]<<(FF_LAMBDA_SHIFT + 6)) - (int)s->lambda * 139);
            if (ff_mpeg2_non_linear_qscale[i] < s->avctx->qmin ||
                (ff_mpeg2_non_linear_qscale[i] > s->avctx->qmax && !s->vbv_ignore_qmax))
                continue;
            if (diff < bestdiff) {
                bestdiff = diff;
                best = i;
            }
        }
        s->qscale = best;
    } else {
        s->qscale = (s->lambda * 139 + FF_LAMBDA_SCALE * 64) >>
                    (FF_LAMBDA_SHIFT + 7);
        s->qscale = av_clip(s->qscale, s->avctx->qmin, s->vbv_ignore_qmax ? 31 : s->avctx->qmax);
    }

    s->lambda2 = (s->lambda * s->lambda + FF_LAMBDA_SCALE / 2) >>
                 FF_LAMBDA_SHIFT;
}