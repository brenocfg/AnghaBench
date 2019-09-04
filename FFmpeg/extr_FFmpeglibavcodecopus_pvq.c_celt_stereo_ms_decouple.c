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

__attribute__((used)) static void celt_stereo_ms_decouple(float *X, float *Y, int N)
{
    int i;
    for (i = 0; i < N; i++) {
        const float Xret = X[i];
        X[i] = (X[i] + Y[i])*M_SQRT1_2;
        Y[i] = (Y[i] - Xret)*M_SQRT1_2;
    }
}