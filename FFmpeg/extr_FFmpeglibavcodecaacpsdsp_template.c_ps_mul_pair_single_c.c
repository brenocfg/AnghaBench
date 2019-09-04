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
typedef  int /*<<< orphan*/  INTFLOAT ;

/* Variables and functions */
 int /*<<< orphan*/  AAC_MUL16 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ps_mul_pair_single_c(INTFLOAT (*dst)[2], INTFLOAT (*src0)[2], INTFLOAT *src1,
                                 int n)
{
    int i;
    for (i = 0; i < n; i++) {
        dst[i][0] = AAC_MUL16(src0[i][0], src1[i]);
        dst[i][1] = AAC_MUL16(src0[i][1], src1[i]);
    }
}