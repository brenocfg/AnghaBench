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
 float FLT_EPSILON ; 
 float sqrtf (float) ; 

__attribute__((used)) static void celt_stereo_is_decouple(float *X, float *Y, float e_l, float e_r, int N)
{
    int i;
    const float energy_n = 1.0f/(sqrtf(e_l*e_l + e_r*e_r) + FLT_EPSILON);
    e_l *= energy_n;
    e_r *= energy_n;
    for (i = 0; i < N; i++)
        X[i] = e_l*X[i] + e_r*Y[i];
}