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
 float* lpc_tab ; 

__attribute__((used)) static void convert_lpc(float *coeff, const int *codes)
{
    int i, j;

    for (i = 0; i < 8; i++) {
        float rc = lpc_tab[codes[i]];
        for (j = 0; j < (i + 1) / 2; j++) {
            float tmp1 = coeff[    j    ];
            float tmp2 = coeff[i - j - 1];
            coeff[    j    ] = tmp1 + rc * tmp2;
            coeff[i - j - 1] = tmp2 + rc * tmp1;
        }
        coeff[i] = rc;
    }
}