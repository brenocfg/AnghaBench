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
union av_intfloat32 {float f; unsigned int i; } ;

/* Variables and functions */

__attribute__((used)) static inline float *VMUL2S(float *dst, const float *v, unsigned idx,
                            unsigned sign, const float *scale)
{
    union av_intfloat32 s0, s1;

    s0.f = s1.f = *scale;
    s0.i ^= sign >> 1 << 31;
    s1.i ^= sign      << 31;

    *dst++ = v[idx    & 15] * s0.f;
    *dst++ = v[idx>>4 & 15] * s1.f;

    return dst;
}