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
 float M_SQRT1_2 ; 

__attribute__((used)) static void celt_haar1(float *X, int N0, int stride)
{
    int i, j;
    N0 >>= 1;
    for (i = 0; i < stride; i++) {
        for (j = 0; j < N0; j++) {
            float x0 = X[stride * (2 * j + 0) + i];
            float x1 = X[stride * (2 * j + 1) + i];
            X[stride * (2 * j + 0) + i] = (x0 + x1) * M_SQRT1_2;
            X[stride * (2 * j + 1) + i] = (x0 - x1) * M_SQRT1_2;
        }
    }
}