#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int int16_t ;
struct TYPE_11__ {scalar_t__ perm_type; int /*<<< orphan*/  idct_permutation; } ;
struct TYPE_10__ {int* scantable; } ;
struct TYPE_9__ {int* scantable; } ;
struct TYPE_8__ {int /*<<< orphan*/  (* fdct ) (int*) ;} ;
struct TYPE_12__ {int y_dc_scale; int c_dc_scale; int** q_intra_matrix; int** q_chroma_intra_matrix; int intra_quant_bias; int** q_inter_matrix; int inter_quant_bias; int max_qcoeff; TYPE_4__ idsp; TYPE_3__ inter_scantable; int /*<<< orphan*/  h263_aic; TYPE_2__ intra_scantable; scalar_t__ mb_intra; int /*<<< orphan*/  (* denoise_dct ) (TYPE_5__*,int*) ;scalar_t__ dct_error_sum; TYPE_1__ fdsp; } ;
typedef  TYPE_5__ MpegEncContext ;

/* Variables and functions */
 scalar_t__ FF_IDCT_PERM_NONE ; 
 int QMAT_SHIFT ; 
 int QUANT_BIAS_SHIFT ; 
 int /*<<< orphan*/  ff_block_permute (int*,int /*<<< orphan*/ ,int const*,int) ; 
 int /*<<< orphan*/  stub1 (int*) ; 
 int /*<<< orphan*/  stub2 (TYPE_5__*,int*) ; 

int ff_dct_quantize_c(MpegEncContext *s,
                        int16_t *block, int n,
                        int qscale, int *overflow)
{
    int i, j, level, last_non_zero, q, start_i;
    const int *qmat;
    const uint8_t *scantable;
    int bias;
    int max=0;
    unsigned int threshold1, threshold2;

    s->fdsp.fdct(block);

    if(s->dct_error_sum)
        s->denoise_dct(s, block);

    if (s->mb_intra) {
        scantable= s->intra_scantable.scantable;
        if (!s->h263_aic) {
            if (n < 4)
                q = s->y_dc_scale;
            else
                q = s->c_dc_scale;
            q = q << 3;
        } else
            /* For AIC we skip quant/dequant of INTRADC */
            q = 1 << 3;

        /* note: block[0] is assumed to be positive */
        block[0] = (block[0] + (q >> 1)) / q;
        start_i = 1;
        last_non_zero = 0;
        qmat = n < 4 ? s->q_intra_matrix[qscale] : s->q_chroma_intra_matrix[qscale];
        bias= s->intra_quant_bias*(1<<(QMAT_SHIFT - QUANT_BIAS_SHIFT));
    } else {
        scantable= s->inter_scantable.scantable;
        start_i = 0;
        last_non_zero = -1;
        qmat = s->q_inter_matrix[qscale];
        bias= s->inter_quant_bias*(1<<(QMAT_SHIFT - QUANT_BIAS_SHIFT));
    }
    threshold1= (1<<QMAT_SHIFT) - bias - 1;
    threshold2= (threshold1<<1);
    for(i=63;i>=start_i;i--) {
        j = scantable[i];
        level = block[j] * qmat[j];

        if(((unsigned)(level+threshold1))>threshold2){
            last_non_zero = i;
            break;
        }else{
            block[j]=0;
        }
    }
    for(i=start_i; i<=last_non_zero; i++) {
        j = scantable[i];
        level = block[j] * qmat[j];

//        if(   bias+level >= (1<<QMAT_SHIFT)
//           || bias-level >= (1<<QMAT_SHIFT)){
        if(((unsigned)(level+threshold1))>threshold2){
            if(level>0){
                level= (bias + level)>>QMAT_SHIFT;
                block[j]= level;
            }else{
                level= (bias - level)>>QMAT_SHIFT;
                block[j]= -level;
            }
            max |=level;
        }else{
            block[j]=0;
        }
    }
    *overflow= s->max_qcoeff < max; //overflow might have happened

    /* we need this permutation so that we correct the IDCT, we only permute the !=0 elements */
    if (s->idsp.perm_type != FF_IDCT_PERM_NONE)
        ff_block_permute(block, s->idsp.idct_permutation,
                      scantable, last_non_zero);

    return last_non_zero;
}