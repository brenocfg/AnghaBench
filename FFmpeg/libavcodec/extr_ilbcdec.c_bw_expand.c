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

__attribute__((used)) static void bw_expand(int16_t *out, const int16_t *in, const int16_t *coef, int length)
{
    int i;

    out[0] = in[0];
    for (i = 1; i < length; i++)
        out[i] = (coef[i] * in[i] + 16384) >> 15;
}