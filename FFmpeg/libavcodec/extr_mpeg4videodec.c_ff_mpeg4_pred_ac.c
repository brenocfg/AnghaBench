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
typedef  int int8_t ;
typedef  int int16_t ;
struct TYPE_6__ {size_t* idct_permutation; } ;
struct TYPE_5__ {int* qscale_table; } ;
struct TYPE_7__ {int*** ac_val; int* block_index; int mb_x; int mb_y; int mb_stride; int qscale; int* block_wrap; TYPE_2__ idsp; scalar_t__ ac_pred; TYPE_1__ current_picture; } ;
typedef  TYPE_3__ MpegEncContext ;

/* Variables and functions */
 scalar_t__ ROUNDED_DIV (int,int) ; 

void ff_mpeg4_pred_ac(MpegEncContext *s, int16_t *block, int n, int dir)
{
    int i;
    int16_t *ac_val, *ac_val1;
    int8_t *const qscale_table = s->current_picture.qscale_table;

    /* find prediction */
    ac_val  = &s->ac_val[0][0][0] + s->block_index[n] * 16;
    ac_val1 = ac_val;
    if (s->ac_pred) {
        if (dir == 0) {
            const int xy = s->mb_x - 1 + s->mb_y * s->mb_stride;
            /* left prediction */
            ac_val -= 16;

            if (s->mb_x == 0 || s->qscale == qscale_table[xy] ||
                n == 1 || n == 3) {
                /* same qscale */
                for (i = 1; i < 8; i++)
                    block[s->idsp.idct_permutation[i << 3]] += ac_val[i];
            } else {
                /* different qscale, we must rescale */
                for (i = 1; i < 8; i++)
                    block[s->idsp.idct_permutation[i << 3]] += ROUNDED_DIV(ac_val[i] * qscale_table[xy], s->qscale);
            }
        } else {
            const int xy = s->mb_x + s->mb_y * s->mb_stride - s->mb_stride;
            /* top prediction */
            ac_val -= 16 * s->block_wrap[n];

            if (s->mb_y == 0 || s->qscale == qscale_table[xy] ||
                n == 2 || n == 3) {
                /* same qscale */
                for (i = 1; i < 8; i++)
                    block[s->idsp.idct_permutation[i]] += ac_val[i + 8];
            } else {
                /* different qscale, we must rescale */
                for (i = 1; i < 8; i++)
                    block[s->idsp.idct_permutation[i]] += ROUNDED_DIV(ac_val[i + 8] * qscale_table[xy], s->qscale);
            }
        }
    }
    /* left copy */
    for (i = 1; i < 8; i++)
        ac_val1[i] = block[s->idsp.idct_permutation[i << 3]];

    /* top copy */
    for (i = 1; i < 8; i++)
        ac_val1[8 + i] = block[s->idsp.idct_permutation[i]];
}