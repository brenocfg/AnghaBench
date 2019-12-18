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
 int /*<<< orphan*/  cos (double) ; 
 int /*<<< orphan*/  sin (double) ; 
 float* twiddles_base_16 (double,float*,int) ; 

__attribute__((used)) static float *twiddles_base_32(double two_pi, float *out, double theta) {
    int i;
    for (i=0; i<16; i++) {
        *out++ = cos(two_pi/32*i + theta);
        *out++ = sin(two_pi/32*i + theta);
    }
    return twiddles_base_16(two_pi, out, 2*theta);
}