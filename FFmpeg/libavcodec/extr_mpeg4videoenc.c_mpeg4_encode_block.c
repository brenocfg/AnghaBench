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
typedef  size_t uint8_t ;
typedef  int uint32_t ;
typedef  int int16_t ;
struct TYPE_3__ {int* block_last_index; scalar_t__ mb_intra; } ;
typedef  int /*<<< orphan*/  PutBitContext ;
typedef  TYPE_1__ MpegEncContext ;

/* Variables and functions */
 int UNI_MPEG4_ENC_INDEX (int,int,int) ; 
 int /*<<< orphan*/  mpeg4_encode_dc (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  put_bits (int /*<<< orphan*/ *,int,int) ; 
 int* uni_mpeg4_inter_rl_bits ; 
 size_t* uni_mpeg4_inter_rl_len ; 
 int* uni_mpeg4_intra_rl_bits ; 
 size_t* uni_mpeg4_intra_rl_len ; 

__attribute__((used)) static inline void mpeg4_encode_block(MpegEncContext *s,
                                      int16_t *block, int n, int intra_dc,
                                      uint8_t *scan_table, PutBitContext *dc_pb,
                                      PutBitContext *ac_pb)
{
    int i, last_non_zero;
    uint32_t *bits_tab;
    uint8_t *len_tab;
    const int last_index = s->block_last_index[n];

    if (s->mb_intra) {  // Note gcc (3.2.1 at least) will optimize this away
        /* MPEG-4 based DC predictor */
        mpeg4_encode_dc(dc_pb, intra_dc, n);
        if (last_index < 1)
            return;
        i = 1;
        bits_tab = uni_mpeg4_intra_rl_bits;
        len_tab  = uni_mpeg4_intra_rl_len;
    } else {
        if (last_index < 0)
            return;
        i = 0;
        bits_tab = uni_mpeg4_inter_rl_bits;
        len_tab  = uni_mpeg4_inter_rl_len;
    }

    /* AC coefs */
    last_non_zero = i - 1;
    for (; i < last_index; i++) {
        int level = block[scan_table[i]];
        if (level) {
            int run = i - last_non_zero - 1;
            level += 64;
            if ((level & (~127)) == 0) {
                const int index = UNI_MPEG4_ENC_INDEX(0, run, level);
                put_bits(ac_pb, len_tab[index], bits_tab[index]);
            } else {  // ESC3
                put_bits(ac_pb,
                         7 + 2 + 1 + 6 + 1 + 12 + 1,
                         (3 << 23) + (3 << 21) + (0 << 20) + (run << 14) +
                         (1 << 13) + (((level - 64) & 0xfff) << 1) + 1);
            }
            last_non_zero = i;
        }
    }
    /* if (i <= last_index) */ {
        int level = block[scan_table[i]];
        int run   = i - last_non_zero - 1;
        level += 64;
        if ((level & (~127)) == 0) {
            const int index = UNI_MPEG4_ENC_INDEX(1, run, level);
            put_bits(ac_pb, len_tab[index], bits_tab[index]);
        } else {  // ESC3
            put_bits(ac_pb,
                     7 + 2 + 1 + 6 + 1 + 12 + 1,
                     (3 << 23) + (3 << 21) + (1 << 20) + (run << 14) +
                     (1 << 13) + (((level - 64) & 0xfff) << 1) + 1);
        }
    }
}