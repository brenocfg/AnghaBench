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

/* Variables and functions */

__attribute__((used)) static inline int compress_coeffs(int *coef, int order, int c_bits)
{
    int i;
    const int low_idx   = c_bits ?  4 : 2;
    const int shift_val = c_bits ?  8 : 4;
    const int high_idx  = c_bits ? 11 : 5;
#ifndef TNS_ENABLE_COEF_COMPRESSION
    return 0;
#endif /* TNS_ENABLE_COEF_COMPRESSION */
    for (i = 0; i < order; i++)
        if (coef[i] >= low_idx && coef[i] <= high_idx)
            return 0;
    for (i = 0; i < order; i++)
        coef[i] -= (coef[i] > high_idx) ? shift_val : 0;
    return 1;
}