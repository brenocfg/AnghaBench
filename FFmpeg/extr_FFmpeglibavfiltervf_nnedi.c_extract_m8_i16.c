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
typedef  int uint8_t ;
typedef  int int16_t ;

/* Variables and functions */
 float FLT_EPSILON ; 
 float sqrt (float) ; 

__attribute__((used)) static void extract_m8_i16(const uint8_t *srcp, const int stride, const int xdia, const int ydia, float *mstd, float *inputf)
{
    int16_t *input = (int16_t *)inputf;
    float scale;
    int sum = 0, sumsq = 0;
    int y, x;

    for (y = 0; y < ydia; y++) {
        const uint8_t *srcpT = srcp + y * stride * 2;
        for (x = 0; x < xdia; x++) {
            sum += srcpT[x];
            sumsq += srcpT[x] * srcpT[x];
            input[x] = srcpT[x];
        }
        input += xdia;
    }
    scale = 1.0f / (float)(xdia * ydia);
    mstd[0] = sum * scale;
    mstd[1] = sumsq * scale - mstd[0] * mstd[0];
    mstd[3] = 0.0f;
    if (mstd[1] <= FLT_EPSILON)
        mstd[1] = mstd[2] = 0.0f;
    else {
        mstd[1] = sqrt(mstd[1]);
        mstd[2] = 1.0f / mstd[1];
    }
}