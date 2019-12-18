#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__* area_q; size_t cno; int* bit_size; int* prev; int* next; int* mb; } ;
typedef  TYPE_1__ EncBlockInfo ;

/* Variables and functions */
 int /*<<< orphan*/  av_assert2 (int) ; 
 scalar_t__ dv_rl2vlc_size (int,int) ; 
 int* ff_dv_quant_offset ; 
 scalar_t__** ff_dv_quant_shifts ; 
 int* mb_area_start ; 
 int vs_total_ac_bits ; 

__attribute__((used)) static inline void dv_guess_qnos(EncBlockInfo *blks, int *qnos)
{
    int size[5];
    int i, j, k, a, prev, a2;
    EncBlockInfo *b;

    size[0] =
    size[1] =
    size[2] =
    size[3] =
    size[4] = 1 << 24;
    do {
        b = blks;
        for (i = 0; i < 5; i++) {
            if (!qnos[i])
                continue;

            qnos[i]--;
            size[i] = 0;
            for (j = 0; j < 6; j++, b++) {
                for (a = 0; a < 4; a++) {
                    if (b->area_q[a] != ff_dv_quant_shifts[qnos[i] + ff_dv_quant_offset[b->cno]][a]) {
                        b->bit_size[a] = 1; // 4 areas 4 bits for EOB :)
                        b->area_q[a]++;
                        prev = b->prev[a];
                        av_assert2(b->next[prev] >= mb_area_start[a + 1] || b->mb[prev]);
                        for (k = b->next[prev]; k < mb_area_start[a + 1]; k = b->next[k]) {
                            b->mb[k] >>= 1;
                            if (b->mb[k]) {
                                b->bit_size[a] += dv_rl2vlc_size(k - prev - 1, b->mb[k]);
                                prev            = k;
                            } else {
                                if (b->next[k] >= mb_area_start[a + 1] && b->next[k] < 64) {
                                    for (a2 = a + 1; b->next[k] >= mb_area_start[a2 + 1]; a2++)
                                        b->prev[a2] = prev;
                                    av_assert2(a2 < 4);
                                    av_assert2(b->mb[b->next[k]]);
                                    b->bit_size[a2] += dv_rl2vlc_size(b->next[k] - prev - 1, b->mb[b->next[k]]) -
                                                       dv_rl2vlc_size(b->next[k] - k    - 1, b->mb[b->next[k]]);
                                    av_assert2(b->prev[a2] == k && (a2 + 1 >= 4 || b->prev[a2 + 1] != k));
                                    b->prev[a2] = prev;
                                }
                                b->next[prev] = b->next[k];
                            }
                        }
                        b->prev[a + 1] = prev;
                    }
                    size[i] += b->bit_size[a];
                }
            }
            if (vs_total_ac_bits >= size[0] + size[1] + size[2] + size[3] + size[4])
                return;
        }
    } while (qnos[0] | qnos[1] | qnos[2] | qnos[3] | qnos[4]);

    for (a = 2; a == 2 || vs_total_ac_bits < size[0]; a += a) {
        b       = blks;
        size[0] = 5 * 6 * 4; // EOB
        for (j = 0; j < 6 * 5; j++, b++) {
            prev = b->prev[0];
            for (k = b->next[prev]; k < 64; k = b->next[k]) {
                if (b->mb[k] < a && b->mb[k] > -a) {
                    b->next[prev] = b->next[k];
                } else {
                    size[0] += dv_rl2vlc_size(k - prev - 1, b->mb[k]);
                    prev     = k;
                }
            }
        }
    }
}