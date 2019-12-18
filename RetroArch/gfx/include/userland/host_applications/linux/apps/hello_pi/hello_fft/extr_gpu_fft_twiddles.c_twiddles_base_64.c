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
 float* twiddles_base_32 (double,float*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static float *twiddles_base_64(double two_pi, float *out) {
    int i;
    for (i=0; i<32; i++) {
        *out++ = cos(two_pi/64*i);
        *out++ = sin(two_pi/64*i);
    }
    return twiddles_base_32(two_pi, out, 0);
}