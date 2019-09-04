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
typedef  float int32_t ;

/* Variables and functions */

__attribute__((used)) static void int32_to_float_fmul_scalar_c(float *dst, const int32_t *src,
                                         float mul, int len)
{
    int i;
    for(i=0; i<len; i++)
        dst[i] = src[i] * mul;
}