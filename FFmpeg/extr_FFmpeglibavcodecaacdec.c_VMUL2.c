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

__attribute__((used)) static inline float *VMUL2(float *dst, const float *v, unsigned idx,
                           const float *scale)
{
    float s = *scale;
    *dst++ = v[idx    & 15] * s;
    *dst++ = v[idx>>4 & 15] * s;
    return dst;
}