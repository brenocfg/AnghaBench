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

__attribute__((used)) static inline void idct_row(int16_t *blk)
{
    int tmp0, tmp1, tmp2, tmp3, tmp4, tmp5, tmp6, tmp7, tmp8, tmp9, tmpA;
    int tmpB, tmpC, tmpD, tmpE, tmpF, tmp10, tmp11, tmp12, tmp13, tmp14;

    tmp0 = blk[5] - blk[3];
    tmp1 = blk[5] + blk[3];
    tmp2 = blk[1] - blk[7];
    tmp3 = blk[1] + blk[7];
    tmp4 = tmp3 - tmp1;
    tmp5 = IDCTMUL(tmp0 + tmp2, FIX_1_847);
    tmp6 = IDCTMUL(tmp2,        FIX_1_082) - tmp5;
    tmp7 = tmp5 - IDCTMUL(tmp0, FIX_2_613) * 2;
    tmp8 = tmp3 + tmp1;
    tmp9 = tmp7 * 4 - tmp8;
    tmpA = IDCTMUL(tmp4, FIX_1_414) * 4 - tmp9;
    tmpB = tmp6 * 4 + tmpA;
    tmpC = blk[2] + blk[6];
    tmpD = blk[2] - blk[6];
    tmpE = blk[0] - blk[4];
    tmpF = blk[0] + blk[4];

    tmp10 = IDCTMUL(tmpD, FIX_1_414) * 4 - tmpC;
    tmp11 = tmpE - tmp10;
    tmp12 = tmpF - tmpC;
    tmp13 = tmpE + tmp10;
    tmp14 = tmpF + tmpC;

    blk[0] = tmp14 + tmp8;
    blk[1] = tmp13 + tmp9;
    blk[2] = tmp11 + tmpA;
    blk[3] = tmp12 - tmpB;
    blk[4] = tmp12 + tmpB;
    blk[5] = tmp11 - tmpA;
    blk[6] = tmp13 - tmp9;
    blk[7] = tmp14 - tmp8;
}