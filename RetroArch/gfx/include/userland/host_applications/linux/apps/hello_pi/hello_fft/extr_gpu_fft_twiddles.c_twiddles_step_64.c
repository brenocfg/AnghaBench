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
 int /*<<< orphan*/  ALPHA (double) ; 
 int /*<<< orphan*/  BETA (double) ; 
 float* twiddles_step_32 (double,float*,int) ; 

__attribute__((used)) static float *twiddles_step_64(double two_pi, float *out, double theta) {
    int i;
    for (i=0; i<32; i++) {
        *out++ = ALPHA(theta);
        *out++ =  BETA(theta);
    }
    return twiddles_step_32(two_pi, out, 2*theta);
}