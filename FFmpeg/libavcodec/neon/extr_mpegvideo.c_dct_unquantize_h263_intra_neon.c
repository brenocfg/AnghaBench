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
struct TYPE_5__ {int y_dc_scale; int c_dc_scale; size_t* block_last_index; TYPE_1__ inter_scantable; scalar_t__ ac_pred; int /*<<< orphan*/  h263_aic; } ;
typedef  TYPE_2__ MpegEncContext ;

/* Variables and functions */
 int /*<<< orphan*/  ff_dct_unquantize_h263_neon (int,int,int,int*) ; 

__attribute__((used)) static void dct_unquantize_h263_intra_neon(MpegEncContext *s, int16_t *block,
                                           int n, int qscale)
{
    int qadd;
    int nCoeffs, blk0;

    if (!s->h263_aic) {
        if (n < 4)
            block[0] *= s->y_dc_scale;
        else
            block[0] *= s->c_dc_scale;
        qadd = (qscale - 1) | 1;
    } else {
        qadd = 0;
    }

    if (s->ac_pred) {
        nCoeffs = 63;
    } else {
        nCoeffs = s->inter_scantable.raster_end[s->block_last_index[n]];
        if (nCoeffs <= 0)
            return;
    }

    blk0 = block[0];

    ff_dct_unquantize_h263_neon(qscale, qadd, nCoeffs + 1, block);

    block[0] = blk0;
}