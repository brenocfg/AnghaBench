#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint8_t ;
typedef  int int8_t ;
typedef  int int16_t ;
struct TYPE_10__ {size_t* permutated; } ;
struct TYPE_13__ {size_t* idct_permutation; } ;
struct TYPE_14__ {size_t* permutated; } ;
struct TYPE_12__ {size_t* permutated; } ;
struct TYPE_11__ {int* qscale_table; } ;
struct TYPE_15__ {int* block_last_index; int*** ac_val; int* block_index; int mb_x; int mb_y; int mb_stride; int* block_wrap; int qscale; TYPE_1__ intra_v_scantable; TYPE_4__ idsp; TYPE_5__ intra_h_scantable; TYPE_3__ intra_scantable; TYPE_2__ current_picture; } ;
typedef  TYPE_6__ MpegEncContext ;

/* Variables and functions */
 int ROUNDED_DIV (int,int) ; 
 scalar_t__ get_block_rate (TYPE_6__*,int*,int,size_t*) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 int /*<<< orphan*/  restore_ac_coeffs (TYPE_6__*,int**,int const*,size_t**,int*) ; 

__attribute__((used)) static inline int decide_ac_pred(MpegEncContext *s, int16_t block[6][64],
                                 const int dir[6], uint8_t *st[6],
                                 int zigzag_last_index[6])
{
    int score = 0;
    int i, n;
    int8_t *const qscale_table = s->current_picture.qscale_table;

    memcpy(zigzag_last_index, s->block_last_index, sizeof(int) * 6);

    for (n = 0; n < 6; n++) {
        int16_t *ac_val, *ac_val1;

        score -= get_block_rate(s, block[n], s->block_last_index[n],
                                s->intra_scantable.permutated);

        ac_val  = s->ac_val[0][0] + s->block_index[n] * 16;
        ac_val1 = ac_val;
        if (dir[n]) {
            const int xy = s->mb_x + s->mb_y * s->mb_stride - s->mb_stride;
            /* top prediction */
            ac_val -= s->block_wrap[n] * 16;
            if (s->mb_y == 0 || s->qscale == qscale_table[xy] || n == 2 || n == 3) {
                /* same qscale */
                for (i = 1; i < 8; i++) {
                    const int level = block[n][s->idsp.idct_permutation[i]];
                    block[n][s->idsp.idct_permutation[i]] = level - ac_val[i + 8];
                    ac_val1[i]     = block[n][s->idsp.idct_permutation[i << 3]];
                    ac_val1[i + 8] = level;
                }
            } else {
                /* different qscale, we must rescale */
                for (i = 1; i < 8; i++) {
                    const int level = block[n][s->idsp.idct_permutation[i]];
                    block[n][s->idsp.idct_permutation[i]] = level - ROUNDED_DIV(ac_val[i + 8] * qscale_table[xy], s->qscale);
                    ac_val1[i]     = block[n][s->idsp.idct_permutation[i << 3]];
                    ac_val1[i + 8] = level;
                }
            }
            st[n] = s->intra_h_scantable.permutated;
        } else {
            const int xy = s->mb_x - 1 + s->mb_y * s->mb_stride;
            /* left prediction */
            ac_val -= 16;
            if (s->mb_x == 0 || s->qscale == qscale_table[xy] || n == 1 || n == 3) {
                /* same qscale */
                for (i = 1; i < 8; i++) {
                    const int level = block[n][s->idsp.idct_permutation[i << 3]];
                    block[n][s->idsp.idct_permutation[i << 3]] = level - ac_val[i];
                    ac_val1[i]     = level;
                    ac_val1[i + 8] = block[n][s->idsp.idct_permutation[i]];
                }
            } else {
                /* different qscale, we must rescale */
                for (i = 1; i < 8; i++) {
                    const int level = block[n][s->idsp.idct_permutation[i << 3]];
                    block[n][s->idsp.idct_permutation[i << 3]] = level - ROUNDED_DIV(ac_val[i] * qscale_table[xy], s->qscale);
                    ac_val1[i]     = level;
                    ac_val1[i + 8] = block[n][s->idsp.idct_permutation[i]];
                }
            }
            st[n] = s->intra_v_scantable.permutated;
        }

        for (i = 63; i > 0; i--)  // FIXME optimize
            if (block[n][st[n][i]])
                break;
        s->block_last_index[n] = i;

        score += get_block_rate(s, block[n], s->block_last_index[n], st[n]);
    }

    if (score < 0) {
        return 1;
    } else {
        restore_ac_coeffs(s, block, dir, st, zigzag_last_index);
        return 0;
    }
}