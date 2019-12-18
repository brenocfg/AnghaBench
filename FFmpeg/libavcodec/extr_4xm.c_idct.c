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
 int /*<<< orphan*/  FIX_1_082392200 ; 
 int /*<<< orphan*/  FIX_1_414213562 ; 
 int /*<<< orphan*/  FIX_1_847759065 ; 
 int /*<<< orphan*/  FIX_2_613125930 ; 
 int MULTIPLY (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void idct(int16_t block[64])
{
    int tmp0, tmp1, tmp2, tmp3, tmp4, tmp5, tmp6, tmp7;
    int tmp10, tmp11, tmp12, tmp13;
    int z5, z10, z11, z12, z13;
    int i;
    int temp[64];

    for (i = 0; i < 8; i++) {
        tmp10 = block[8 * 0 + i] + block[8 * 4 + i];
        tmp11 = block[8 * 0 + i] - block[8 * 4 + i];

        tmp13 = block[8 * 2 + i] + block[8 * 6 + i];
        tmp12 = MULTIPLY(block[8 * 2 + i] - block[8 * 6 + i], FIX_1_414213562) - tmp13;

        tmp0 = tmp10 + tmp13;
        tmp3 = tmp10 - tmp13;
        tmp1 = tmp11 + tmp12;
        tmp2 = tmp11 - tmp12;

        z13 = block[8 * 5 + i] + block[8 * 3 + i];
        z10 = block[8 * 5 + i] - block[8 * 3 + i];
        z11 = block[8 * 1 + i] + block[8 * 7 + i];
        z12 = block[8 * 1 + i] - block[8 * 7 + i];

        tmp7  =          z11 + z13;
        tmp11 = MULTIPLY(z11 - z13, FIX_1_414213562);

        z5    = MULTIPLY(z10 + z12, FIX_1_847759065);
        tmp10 = MULTIPLY(z12,  FIX_1_082392200) - z5;
        tmp12 = MULTIPLY(z10, -FIX_2_613125930) + z5;

        tmp6 = tmp12 - tmp7;
        tmp5 = tmp11 - tmp6;
        tmp4 = tmp10 + tmp5;

        temp[8 * 0 + i] = tmp0 + tmp7;
        temp[8 * 7 + i] = tmp0 - tmp7;
        temp[8 * 1 + i] = tmp1 + tmp6;
        temp[8 * 6 + i] = tmp1 - tmp6;
        temp[8 * 2 + i] = tmp2 + tmp5;
        temp[8 * 5 + i] = tmp2 - tmp5;
        temp[8 * 4 + i] = tmp3 + tmp4;
        temp[8 * 3 + i] = tmp3 - tmp4;
    }

    for (i = 0; i < 8 * 8; i += 8) {
        tmp10 = temp[0 + i] + temp[4 + i];
        tmp11 = temp[0 + i] - temp[4 + i];

        tmp13 = temp[2 + i] + temp[6 + i];
        tmp12 = MULTIPLY(temp[2 + i] - temp[6 + i], FIX_1_414213562) - tmp13;

        tmp0 = tmp10 + tmp13;
        tmp3 = tmp10 - tmp13;
        tmp1 = tmp11 + tmp12;
        tmp2 = tmp11 - tmp12;

        z13 = temp[5 + i] + temp[3 + i];
        z10 = temp[5 + i] - temp[3 + i];
        z11 = temp[1 + i] + temp[7 + i];
        z12 = temp[1 + i] - temp[7 + i];

        tmp7  = z11 + z13;
        tmp11 = MULTIPLY(z11 - z13, FIX_1_414213562);

        z5    = MULTIPLY(z10 + z12, FIX_1_847759065);
        tmp10 = MULTIPLY(z12,  FIX_1_082392200) - z5;
        tmp12 = MULTIPLY(z10, -FIX_2_613125930) + z5;

        tmp6 = tmp12 - tmp7;
        tmp5 = tmp11 - tmp6;
        tmp4 = tmp10 + tmp5;

        block[0 + i] = (tmp0 + tmp7) >> 6;
        block[7 + i] = (tmp0 - tmp7) >> 6;
        block[1 + i] = (tmp1 + tmp6) >> 6;
        block[6 + i] = (tmp1 - tmp6) >> 6;
        block[2 + i] = (tmp2 + tmp5) >> 6;
        block[5 + i] = (tmp2 - tmp5) >> 6;
        block[4 + i] = (tmp3 + tmp4) >> 6;
        block[3 + i] = (tmp3 - tmp4) >> 6;
    }
}