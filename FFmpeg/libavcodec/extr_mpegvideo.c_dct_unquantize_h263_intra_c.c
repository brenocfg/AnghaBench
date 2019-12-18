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
typedef  int int16_t ;
struct TYPE_4__ {int* raster_end; } ;
struct TYPE_5__ {size_t* block_last_index; int y_dc_scale; int c_dc_scale; TYPE_1__ intra_scantable; scalar_t__ ac_pred; scalar_t__ h263_aic; } ;
typedef  TYPE_2__ MpegEncContext ;

/* Variables and functions */
 int /*<<< orphan*/  av_assert2 (int) ; 

__attribute__((used)) static void dct_unquantize_h263_intra_c(MpegEncContext *s,
                                  int16_t *block, int n, int qscale)
{
    int i, level, qmul, qadd;
    int nCoeffs;

    av_assert2(s->block_last_index[n]>=0 || s->h263_aic);

    qmul = qscale << 1;

    if (!s->h263_aic) {
        block[0] *= n < 4 ? s->y_dc_scale : s->c_dc_scale;
        qadd = (qscale - 1) | 1;
    }else{
        qadd = 0;
    }
    if(s->ac_pred)
        nCoeffs=63;
    else
        nCoeffs= s->intra_scantable.raster_end[ s->block_last_index[n] ];

    for(i=1; i<=nCoeffs; i++) {
        level = block[i];
        if (level) {
            if (level < 0) {
                level = level * qmul - qadd;
            } else {
                level = level * qmul + qadd;
            }
            block[i] = level;
        }
    }
}