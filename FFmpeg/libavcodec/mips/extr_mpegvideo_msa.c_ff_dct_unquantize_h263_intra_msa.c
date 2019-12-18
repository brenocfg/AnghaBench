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
typedef  size_t int32_t ;
typedef  int /*<<< orphan*/  int16_t ;
struct TYPE_4__ {size_t* raster_end; } ;
struct TYPE_5__ {size_t* block_last_index; TYPE_1__ inter_scantable; scalar_t__ ac_pred; int /*<<< orphan*/  c_dc_scale; int /*<<< orphan*/  y_dc_scale; scalar_t__ h263_aic; } ;
typedef  TYPE_2__ MpegEncContext ;

/* Variables and functions */
 int /*<<< orphan*/  av_assert2 (int) ; 
 int /*<<< orphan*/  h263_dct_unquantize_msa (int /*<<< orphan*/ *,size_t,size_t,size_t,int) ; 

void ff_dct_unquantize_h263_intra_msa(MpegEncContext *s,
                                      int16_t *block, int32_t index,
                                      int32_t qscale)
{
    int32_t qmul, qadd;
    int32_t nCoeffs;

    av_assert2(s->block_last_index[index] >= 0 || s->h263_aic);

    qmul = qscale << 1;

    if (!s->h263_aic) {
        block[0] *= index < 4 ? s->y_dc_scale : s->c_dc_scale;
        qadd = (qscale - 1) | 1;
    } else {
        qadd = 0;
    }
    if (s->ac_pred)
        nCoeffs = 63;
    else
        nCoeffs = s->inter_scantable.raster_end[s->block_last_index[index]];

    h263_dct_unquantize_msa(block, qmul, qadd, nCoeffs, 1);
}