#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int int16_t ;
struct TYPE_8__ {scalar_t__ perm_type; int /*<<< orphan*/  idct_permutation; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* fdct ) (int*) ;} ;
struct TYPE_6__ {int* scantable; } ;
struct TYPE_9__ {int** q_intra_matrix; int** q_chroma_intra_matrix; int intra_quant_bias; int max_qcoeff; TYPE_3__ idsp; TYPE_2__ fdsp; TYPE_1__ intra_scantable; } ;
typedef  TYPE_4__ MpegEncContext ;

/* Variables and functions */
 scalar_t__ FF_IDCT_PERM_NONE ; 
 int /*<<< orphan*/  ff_block_permute (int*,int /*<<< orphan*/ ,int const*,int) ; 
 int /*<<< orphan*/  stub1 (int*) ; 

__attribute__((used)) static int dnxhd_10bit_dct_quantize_444(MpegEncContext *ctx, int16_t *block,
                                        int n, int qscale, int *overflow)
{
    int i, j, level, last_non_zero, start_i;
    const int *qmat;
    const uint8_t *scantable= ctx->intra_scantable.scantable;
    int bias;
    int max = 0;
    unsigned int threshold1, threshold2;

    ctx->fdsp.fdct(block);

    block[0] = (block[0] + 2) >> 2;
    start_i = 1;
    last_non_zero = 0;
    qmat = n < 4 ? ctx->q_intra_matrix[qscale] : ctx->q_chroma_intra_matrix[qscale];
    bias= ctx->intra_quant_bias * (1 << (16 - 8));
    threshold1 = (1 << 16) - bias - 1;
    threshold2 = (threshold1 << 1);

    for (i = 63; i >= start_i; i--) {
        j = scantable[i];
        level = block[j] * qmat[j];

        if (((unsigned)(level + threshold1)) > threshold2) {
            last_non_zero = i;
            break;
        } else{
            block[j]=0;
        }
    }

    for (i = start_i; i <= last_non_zero; i++) {
        j = scantable[i];
        level = block[j] * qmat[j];

        if (((unsigned)(level + threshold1)) > threshold2) {
            if (level > 0) {
                level = (bias + level) >> 16;
                block[j] = level;
            } else{
                level = (bias - level) >> 16;
                block[j] = -level;
            }
            max |= level;
        } else {
            block[j] = 0;
        }
    }
    *overflow = ctx->max_qcoeff < max; //overflow might have happened

    /* we need this permutation so that we correct the IDCT, we only permute the !=0 elements */
    if (ctx->idsp.perm_type != FF_IDCT_PERM_NONE)
        ff_block_permute(block, ctx->idsp.idct_permutation,
                         scantable, last_non_zero);

    return last_non_zero;
}