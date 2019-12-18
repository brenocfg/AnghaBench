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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  int16_t ;
struct TYPE_6__ {size_t* idct_permutation; } ;
struct TYPE_5__ {int /*<<< orphan*/ * permutated; } ;
struct TYPE_7__ {int* block_index; TYPE_2__ idsp; TYPE_1__ intra_scantable; int /*<<< orphan*/ *** ac_val; int /*<<< orphan*/  block_last_index; } ;
typedef  TYPE_3__ MpegEncContext ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int const*,int) ; 

__attribute__((used)) static inline void restore_ac_coeffs(MpegEncContext *s, int16_t block[6][64],
                                     const int dir[6], uint8_t *st[6],
                                     const int zigzag_last_index[6])
{
    int i, n;
    memcpy(s->block_last_index, zigzag_last_index, sizeof(int) * 6);

    for (n = 0; n < 6; n++) {
        int16_t *ac_val = s->ac_val[0][0] + s->block_index[n] * 16;

        st[n] = s->intra_scantable.permutated;
        if (dir[n]) {
            /* top prediction */
            for (i = 1; i < 8; i++)
                block[n][s->idsp.idct_permutation[i]] = ac_val[i + 8];
        } else {
            /* left prediction */
            for (i = 1; i < 8; i++)
                block[n][s->idsp.idct_permutation[i << 3]] = ac_val[i];
        }
    }
}