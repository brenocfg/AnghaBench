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
 double GPU_FFT_QPUS ; 
 float* twiddles_base_32 (double,float*,double) ; 
 float* twiddles_step_16 (double,float*,double) ; 
 float* twiddles_step_32 (double,float*,double) ; 

__attribute__((used)) static void twiddles_512k(double two_pi, float *out) {
    double N=512*1024;
    int q;

    out = twiddles_base_32(two_pi, out, 0);
    out = twiddles_step_16(two_pi, out, two_pi/N * 32*32);
    out = twiddles_step_32(two_pi, out, two_pi/N * 32);
    out = twiddles_step_32(two_pi, out, two_pi/N * GPU_FFT_QPUS);

    for (q=0; q<GPU_FFT_QPUS; q++)
        out = twiddles_base_32(two_pi, out, two_pi/N*q);
}