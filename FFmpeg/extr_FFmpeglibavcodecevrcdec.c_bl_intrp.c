#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int int16_t ;
struct TYPE_3__ {float* interpolation_coeffs; } ;
typedef  TYPE_1__ EVRCContext ;

/* Variables and functions */
 int lrintf (float) ; 

__attribute__((used)) static void bl_intrp(EVRCContext *e, float *ex, float delay)
{
    float *f;
    int offset, i, coef_idx;
    int16_t t;

    offset = lrintf(delay);

    t = (offset - delay + 0.5) * 8.0 + 0.5;
    if (t == 8) {
        t = 0;
        offset--;
    }

    f = ex - offset - 8;

    coef_idx = t * (2 * 8 + 1);

    ex[0] = 0.0;
    for (i = 0; i < 2 * 8 + 1; i++)
        ex[0] += e->interpolation_coeffs[coef_idx + i] * f[i];
}