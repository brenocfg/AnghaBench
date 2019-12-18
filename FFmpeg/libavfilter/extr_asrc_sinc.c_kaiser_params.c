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
 float M_PI ; 
 int ceilf (float) ; 
 float kaiser_beta (float,float) ; 

__attribute__((used)) static void kaiser_params(float att, float Fc, float tr_bw, float *beta, int *num_taps)
{
    *beta = *beta < 0.f ? kaiser_beta(att, tr_bw * .5f / Fc): *beta;
    att = att < 60.f ? (att - 7.95f) / (2.285f * M_PI * 2.f) :
        ((.0007528358f-1.577737e-05 * *beta) * *beta + 0.6248022f) * *beta + .06186902f;
    *num_taps = !*num_taps ? ceilf(att/tr_bw + 1) : *num_taps;
}