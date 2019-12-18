#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int uint32_t ;
typedef  int int32_t ;

/* Variables and functions */
 int FFABS (int) ; 
 int SCALE_OUT_BITS ; 
 int ff_clz (int) ; 

__attribute__((used)) static int sbc_calc_scalefactors_j(int32_t sb_sample_f[16][2][8],
                                   uint32_t scale_factor[2][8],
                                   int blocks, int subbands)
{
    int blk, joint = 0;
    int32_t tmp0, tmp1;
    uint32_t x, y;

    /* last subband does not use joint stereo */
    int sb = subbands - 1;
    x = 1 << SCALE_OUT_BITS;
    y = 1 << SCALE_OUT_BITS;
    for (blk = 0; blk < blocks; blk++) {
        tmp0 = FFABS(sb_sample_f[blk][0][sb]);
        tmp1 = FFABS(sb_sample_f[blk][1][sb]);
        if (tmp0 != 0)
            x |= tmp0 - 1;
        if (tmp1 != 0)
            y |= tmp1 - 1;
    }
    scale_factor[0][sb] = (31 - SCALE_OUT_BITS) - ff_clz(x);
    scale_factor[1][sb] = (31 - SCALE_OUT_BITS) - ff_clz(y);

    /* the rest of subbands can use joint stereo */
    while (--sb >= 0) {
        int32_t sb_sample_j[16][2];
        x = 1 << SCALE_OUT_BITS;
        y = 1 << SCALE_OUT_BITS;
        for (blk = 0; blk < blocks; blk++) {
            tmp0 = sb_sample_f[blk][0][sb];
            tmp1 = sb_sample_f[blk][1][sb];
            sb_sample_j[blk][0] = (tmp0 >> 1) + (tmp1 >> 1);
            sb_sample_j[blk][1] = (tmp0 >> 1) - (tmp1 >> 1);
            tmp0 = FFABS(tmp0);
            tmp1 = FFABS(tmp1);
            if (tmp0 != 0)
                x |= tmp0 - 1;
            if (tmp1 != 0)
                y |= tmp1 - 1;
        }
        scale_factor[0][sb] = (31 - SCALE_OUT_BITS) -
            ff_clz(x);
        scale_factor[1][sb] = (31 - SCALE_OUT_BITS) -
            ff_clz(y);
        x = 1 << SCALE_OUT_BITS;
        y = 1 << SCALE_OUT_BITS;
        for (blk = 0; blk < blocks; blk++) {
            tmp0 = FFABS(sb_sample_j[blk][0]);
            tmp1 = FFABS(sb_sample_j[blk][1]);
            if (tmp0 != 0)
                x |= tmp0 - 1;
            if (tmp1 != 0)
                y |= tmp1 - 1;
        }
        x = (31 - SCALE_OUT_BITS) - ff_clz(x);
        y = (31 - SCALE_OUT_BITS) - ff_clz(y);

        /* decide whether to use joint stereo for this subband */
        if ((scale_factor[0][sb] + scale_factor[1][sb]) > x + y) {
            joint |= 1 << (subbands - 1 - sb);
            scale_factor[0][sb] = x;
            scale_factor[1][sb] = y;
            for (blk = 0; blk < blocks; blk++) {
                sb_sample_f[blk][0][sb] = sb_sample_j[blk][0];
                sb_sample_f[blk][1][sb] = sb_sample_j[blk][1];
            }
        }
    }

    /* bitmask with the information about subbands using joint stereo */
    return joint;
}