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
 float const CELT_EMPH_COEFF ; 

__attribute__((used)) static float deemphasis_c(float *y, float *x, float coeff, int len)
{
    float state = coeff;

    for (int i = 0; i < len; i++) {
        const float tmp = x[i] + state;
        state = tmp * CELT_EMPH_COEFF;
        y[i] = tmp;
    }

    return state;
}