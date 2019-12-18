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
typedef  int /*<<< orphan*/  IMCContext ;

/* Variables and functions */
 int BANDS ; 
 double exp2 (int) ; 
 float* imc_exp_tab ; 
 float log2f (float) ; 

__attribute__((used)) static void imc_decode_level_coefficients(IMCContext *q, int *levlCoeffBuf,
                                          float *flcoeffs1, float *flcoeffs2)
{
    int i, level;
    float tmp, tmp2;
    // maybe some frequency division thingy

    flcoeffs1[0] = 20000.0 / exp2 (levlCoeffBuf[0] * 0.18945); // 0.18945 = log2(10) * 0.05703125
    flcoeffs2[0] = log2f(flcoeffs1[0]);
    tmp  = flcoeffs1[0];
    tmp2 = flcoeffs2[0];

    for (i = 1; i < BANDS; i++) {
        level = levlCoeffBuf[i];
        if (level == 16) {
            flcoeffs1[i] = 1.0;
            flcoeffs2[i] = 0.0;
        } else {
            if (level < 17)
                level -= 7;
            else if (level <= 24)
                level -= 32;
            else
                level -= 16;

            tmp  *= imc_exp_tab[15 + level];
            tmp2 += 0.83048 * level;  // 0.83048 = log2(10) * 0.25
            flcoeffs1[i] = tmp;
            flcoeffs2[i] = tmp2;
        }
    }
}