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

__attribute__((used)) static inline void idct_row(int16_t *blk)
{
    int t0, t1, t2, t3, t4, t5, t6, t7, t8, t9, tA, tB, tC, tD, tE, tF;
    int t10, t11, t12, t13;

    t0  =  (blk[3] * 19266 + blk[5] * 12873) >> 14;
    t1  =  (blk[5] * 19266 - blk[3] * 12873) >> 14;
    t2  = ((blk[7] * 4520  + blk[1] * 22725) >> 14) - t0;
    t3  = ((blk[1] * 4520  - blk[7] * 22725) >> 14) - t1;
    t4  = t0 * 2 + t2;
    t5  = t1 * 2 + t3;
    t6  = t2 - t3;
    t7  = t3 * 2 + t6;
    t8  = (t6 * 11585) >> 14;
    t9  = (t7 * 11585) >> 14;
    tA  = (blk[2] * 8867 - blk[6] * 21407) >> 14;
    tB  = (blk[6] * 8867 + blk[2] * 21407) >> 14;
    tC  = blk[0] - blk[4];
    tD  = blk[4] * 2 + tC;
    tE  = tC - tA;
    tF  = tD - tB;
    t10 = tF - t5;
    t11 = tE - t8;
    t12 = tE + tA * 2 - t9;
    t13 = tF + tB * 2 - t4;

    blk[0] = (t13 + t4 * 2 + 4) >> 3;
    blk[1] = (t12 + t9 * 2 + 4) >> 3;
    blk[2] = (t11 + t8 * 2 + 4) >> 3;
    blk[3] = (t10 + t5 * 2 + 4) >> 3;
    blk[4] = (t10          + 4) >> 3;
    blk[5] = (t11          + 4) >> 3;
    blk[6] = (t12          + 4) >> 3;
    blk[7] = (t13          + 4) >> 3;
}