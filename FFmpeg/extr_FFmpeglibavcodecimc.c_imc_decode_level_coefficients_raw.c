#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int coef0_pos; } ;
typedef  TYPE_1__ IMCContext ;

/* Variables and functions */
 int BANDS ; 
 float log2f (float) ; 
 double pow (int,int) ; 
 float powf (double,int) ; 

__attribute__((used)) static void imc_decode_level_coefficients_raw(IMCContext *q, int *levlCoeffBuf,
                                              float *flcoeffs1, float *flcoeffs2)
{
    int i, level, pos;
    float tmp, tmp2;

    pos = q->coef0_pos;
    flcoeffs1[pos] = 20000.0 / pow (2, levlCoeffBuf[0] * 0.18945); // 0.18945 = log2(10) * 0.05703125
    flcoeffs2[pos] = log2f(flcoeffs1[pos]);
    tmp  = flcoeffs1[pos];
    tmp2 = flcoeffs2[pos];

    levlCoeffBuf++;
    for (i = 0; i < BANDS; i++) {
        if (i == pos)
            continue;
        level = *levlCoeffBuf++;
        flcoeffs1[i] = tmp  * powf(10.0, -level * 0.4375); //todo tab
        flcoeffs2[i] = tmp2 - 1.4533435415 * level; // 1.4533435415 = log2(10) * 0.4375
    }
}