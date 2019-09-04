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
typedef  int int16_t ;

/* Variables and functions */
 int /*<<< orphan*/  FIX_1_082 ; 
 int /*<<< orphan*/  FIX_1_414 ; 
 int /*<<< orphan*/  FIX_1_847 ; 
 int /*<<< orphan*/  FIX_2_613 ; 
 int IDCTMUL (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void idct_col(int16_t *blk)
{
    int tmp0, tmp1, tmp2, tmp3, tmp4, tmp5, tmp6, tmp7, tmp8, tmp9, tmpA;
    int tmpB, tmpC, tmpD, tmpE, tmpF, tmp10, tmp11, tmp12, tmp13, tmp14;

    tmp0 = blk[5 * 8] - blk[3 * 8];
    tmp1 = blk[5 * 8] + blk[3 * 8];
    tmp2 = blk[1 * 8] * 2 - (blk[7 * 8] >> 2);
    tmp3 = blk[1 * 8] * 2 + (blk[7 * 8] >> 2);
    tmp4 = tmp3 - tmp1;
    tmp5 = IDCTMUL(tmp0 + tmp2, FIX_1_847);
    tmp6 = IDCTMUL(tmp2,        FIX_1_082) - tmp5;
    tmp7 = tmp5 - IDCTMUL(tmp0, FIX_2_613) * 2;
    tmp8 = (tmp3 + tmp1) >> 1;
    tmp9 = tmp7 * 2 - tmp8;
    tmpA = IDCTMUL(tmp4, FIX_1_414) * 2 - tmp9;
    tmpB = tmp6 * 2 + tmpA;
    tmpC =  blk[2 * 8] + (blk[6 * 8] >> 1) >> 1;
    tmpD =  blk[2 * 8] - (blk[6 * 8] >> 1);
    tmpE = (blk[0 * 8] >> 1) - (blk[4 * 8] >> 1) + 0x2020;
    tmpF = (blk[0 * 8] >> 1) + (blk[4 * 8] >> 1) + 0x2020;

    tmp10 = IDCTMUL(tmpD, FIX_1_414) * 2 - tmpC;
    tmp11 = tmpE - tmp10;
    tmp12 = tmpF - tmpC;
    tmp13 = tmpE + tmp10;
    tmp14 = tmpF + tmpC;

    blk[0 * 8] = (tmp14 + tmp8) >> 6;
    blk[1 * 8] = (tmp13 + tmp9) >> 6;
    blk[2 * 8] = (tmp11 + tmpA) >> 6;
    blk[3 * 8] = (tmp12 - tmpB) >> 6;
    blk[4 * 8] = (tmp12 + tmpB) >> 6;
    blk[5 * 8] = (tmp11 - tmpA) >> 6;
    blk[6 * 8] = (tmp13 - tmp9) >> 6;
    blk[7 * 8] = (tmp14 - tmp8) >> 6;
}