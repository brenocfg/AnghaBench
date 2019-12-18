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

__attribute__((used)) static void lsf_interpolate(int16_t *out, int16_t *in1,
                            int16_t *in2, int16_t coef,
                            int size)
{
    int invcoef = 16384 - coef, i;

    for (i = 0; i < size; i++)
        out[i] = (coef * in1[i] + invcoef * in2[i] + 8192) >> 14;
}