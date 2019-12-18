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

__attribute__((used)) static inline void calculate_bicubic_coeffs(float t, float *coeffs)
{
    const float tt  = t * t;
    const float ttt = t * t * t;

    coeffs[0] =     - t / 3.f + tt / 2.f - ttt / 6.f;
    coeffs[1] = 1.f - t / 2.f - tt       + ttt / 2.f;
    coeffs[2] =       t       + tt / 2.f - ttt / 2.f;
    coeffs[3] =     - t / 6.f            + ttt / 6.f;
}