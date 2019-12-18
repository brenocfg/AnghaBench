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
 double* k ; 

__attribute__((used)) static float *twiddles_step_16(double two_pi, float *out, double theta) {
    int i;
    for (i=0; i<16; i++) {
        *out++ = ALPHA(theta*k[i]);
        *out++ =  BETA(theta*k[i]);
    }
    return out;
}