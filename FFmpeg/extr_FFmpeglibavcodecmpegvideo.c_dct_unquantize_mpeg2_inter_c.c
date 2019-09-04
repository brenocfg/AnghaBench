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
typedef  scalar_t__ uint16_t ;
typedef  int int16_t ;
struct TYPE_4__ {int* permutated; } ;
struct TYPE_5__ {int* block_last_index; TYPE_1__ intra_scantable; scalar_t__* inter_matrix; scalar_t__ alternate_scan; scalar_t__ q_scale_type; } ;
typedef  TYPE_2__ MpegEncContext ;

/* Variables and functions */
 int* ff_mpeg2_non_linear_qscale ; 

__attribute__((used)) static void dct_unquantize_mpeg2_inter_c(MpegEncContext *s,
                                   int16_t *block, int n, int qscale)
{
    int i, level, nCoeffs;
    const uint16_t *quant_matrix;
    int sum=-1;

    if (s->q_scale_type) qscale = ff_mpeg2_non_linear_qscale[qscale];
    else                 qscale <<= 1;

    if(s->alternate_scan) nCoeffs= 63;
    else nCoeffs= s->block_last_index[n];

    quant_matrix = s->inter_matrix;
    for(i=0; i<=nCoeffs; i++) {
        int j= s->intra_scantable.permutated[i];
        level = block[j];
        if (level) {
            if (level < 0) {
                level = -level;
                level = (((level << 1) + 1) * qscale *
                         ((int) (quant_matrix[j]))) >> 5;
                level = -level;
            } else {
                level = (((level << 1) + 1) * qscale *
                         ((int) (quant_matrix[j]))) >> 5;
            }
            block[j] = level;
            sum+=level;
        }
    }
    block[63]^=sum&1;
}