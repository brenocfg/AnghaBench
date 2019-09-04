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
typedef  int int16_t ;

/* Variables and functions */

__attribute__((used)) static int32_t scalarproduct_and_madd_int32_c(int16_t *v1, const int32_t *v2,
                                              const int16_t *v3,
                                              int order, int mul)
{
    int res = 0;

    do {
        res   += *v1 * (uint32_t)*v2++;
        *v1++ += mul * *v3++;
        res   += *v1 * (uint32_t)*v2++;
        *v1++ += mul * *v3++;
    } while (order-=2);
    return res;
}