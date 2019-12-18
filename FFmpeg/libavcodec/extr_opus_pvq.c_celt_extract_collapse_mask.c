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

/* Variables and functions */

__attribute__((used)) static inline uint32_t celt_extract_collapse_mask(const int *iy, uint32_t N, uint32_t B)
{
    int i, j, N0 = N / B;
    uint32_t collapse_mask = 0;

    if (B <= 1)
        return 1;

    for (i = 0; i < B; i++)
        for (j = 0; j < N0; j++)
            collapse_mask |= (!!iy[i*N0+j]) << i;
    return collapse_mask;
}