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

__attribute__((used)) static void celt_exp_rotation_impl(float *X, uint32_t len, uint32_t stride,
                                   float c, float s)
{
    float *Xptr;
    int i;

    Xptr = X;
    for (i = 0; i < len - stride; i++) {
        float x1     = Xptr[0];
        float x2     = Xptr[stride];
        Xptr[stride] = c * x2 + s * x1;
        *Xptr++      = c * x1 - s * x2;
    }

    Xptr = &X[len - 2 * stride - 1];
    for (i = len - 2 * stride - 1; i >= 0; i--) {
        float x1     = Xptr[0];
        float x2     = Xptr[stride];
        Xptr[stride] = c * x2 + s * x1;
        *Xptr--      = c * x1 - s * x2;
    }
}