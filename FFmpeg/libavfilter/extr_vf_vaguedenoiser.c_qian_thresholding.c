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
 float FFABS (float) ; 

__attribute__((used)) static void qian_thresholding(float *block, const int width, const int height,
                              const int stride, const float threshold,
                              const float percent, const int unused)
{
    const float percent01 = percent * 0.01f;
    const float tr2 = threshold * threshold * percent01;
    const float frac = 1.f - percent01;
    int y, x;

    for (y = 0; y < height; y++) {
        for (x = 0; x < width; x++) {
            const float temp = FFABS(block[x]);
            if (temp <= threshold) {
                block[x] *= frac;
            } else {
                const float tp2 = temp * temp;
                block[x] *= (tp2 - tr2) / tp2;
            }
        }
        block += stride;
    }
}