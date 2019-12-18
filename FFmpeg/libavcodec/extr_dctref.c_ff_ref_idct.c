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
 short* coefficients ; 
 short floor (double) ; 

void ff_ref_idct(short *block)
{
    /* implement the equation: block = (coefficients') * block * coefficients */

    unsigned int i, j, k;
    double out[8 * 8];

    /* out = block * coefficients */
    for (i = 0; i < 64; i += 8) {
        for (j = 0; j < 8; ++j) {
            double tmp = 0;
            for (k = 0; k < 8; ++k) {
                tmp += block[i + k] * coefficients[k * 8 + j];
            }
            out[i + j] = tmp;
        }
    }

    /* block = (coefficients') * out */
    for (i = 0; i < 8; ++i) {
        for (j = 0; j < 8; ++j) {
            double tmp = 0;
            for (k = 0; k < 64; k += 8) {
                tmp += coefficients[k + i] * out[k + j];
            }
            block[i * 8 + j] = floor(tmp + 0.5);
        }
    }
}