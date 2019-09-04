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
 float* imc_exp_tab2 ; 

__attribute__((used)) static void imc_decode_level_coefficients2(IMCContext *q, int *levlCoeffBuf,
                                           float *old_floor, float *flcoeffs1,
                                           float *flcoeffs2)
{
    int i;
    /* FIXME maybe flag_buf = noise coding and flcoeffs1 = new scale factors
     *       and flcoeffs2 old scale factors
     *       might be incomplete due to a missing table that is in the binary code
     */
    for (i = 0; i < BANDS; i++) {
        flcoeffs1[i] = 0;
        if (levlCoeffBuf[i] < 16) {
            flcoeffs1[i] = imc_exp_tab2[levlCoeffBuf[i]] * old_floor[i];
            flcoeffs2[i] = (levlCoeffBuf[i] - 7) * 0.83048 + flcoeffs2[i]; // 0.83048 = log2(10) * 0.25
        } else {
            flcoeffs1[i] = old_floor[i];
        }
    }
}