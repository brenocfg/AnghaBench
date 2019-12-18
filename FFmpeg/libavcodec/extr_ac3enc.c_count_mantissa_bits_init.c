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
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  mant_cnt ;

/* Variables and functions */
 int AC3_MAX_BLOCKS ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void count_mantissa_bits_init(uint16_t mant_cnt[AC3_MAX_BLOCKS][16])
{
    int blk;

    for (blk = 0; blk < AC3_MAX_BLOCKS; blk++) {
        memset(mant_cnt[blk], 0, sizeof(mant_cnt[blk]));
        mant_cnt[blk][1] = mant_cnt[blk][2] = 2;
        mant_cnt[blk][4] = 1;
    }
}