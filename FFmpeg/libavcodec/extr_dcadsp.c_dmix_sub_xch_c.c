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
typedef  int ptrdiff_t ;
typedef  scalar_t__ int32_t ;

/* Variables and functions */
 scalar_t__ mul23 (scalar_t__ const,int) ; 

__attribute__((used)) static void dmix_sub_xch_c(int32_t *dst1, int32_t *dst2,
                           const int32_t *src, ptrdiff_t len)
{
    int i;

    for (i = 0; i < len; i++) {
        int32_t cs = mul23(src[i], 5931520 /* M_SQRT1_2 * (1 << 23) */);
        dst1[i] -= cs;
        dst2[i] -= cs;
    }
}