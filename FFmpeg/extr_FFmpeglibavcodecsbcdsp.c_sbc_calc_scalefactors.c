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

__attribute__((used)) static void sbc_calc_scalefactors(int32_t sb_sample_f[16][2][8],
                                  uint32_t scale_factor[2][8],
                                  int blocks, int channels, int subbands)
{
    int ch, sb, blk;
    for (ch = 0; ch < channels; ch++) {
        for (sb = 0; sb < subbands; sb++) {
            uint32_t x = 1 << SCALE_OUT_BITS;
            for (blk = 0; blk < blocks; blk++) {
                int32_t tmp = FFABS(sb_sample_f[blk][ch][sb]);
                if (tmp != 0)
                    x |= tmp - 1;
            }
            scale_factor[ch][sb] = (31 - SCALE_OUT_BITS) - ff_clz(x);
        }
    }
}