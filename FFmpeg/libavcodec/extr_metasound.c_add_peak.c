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
 int ROUNDED_DIV (int,int) ; 

__attribute__((used)) static void add_peak(float period, int width, const float *shape,
                     float ppc_gain, float *speech, int len)
{
    int i, j, center;
    const float *shape_end = shape + len;

    // First peak centered around zero
    for (i = 0; i < width / 2; i++)
        speech[i] += ppc_gain * *shape++;

    for (i = 1; i < ROUNDED_DIV(len, width); i++) {
        center = (int)(i * period + 0.5);
        for (j = -width / 2; j < (width + 1) / 2; j++)
            speech[j + center] += ppc_gain * *shape++;
    }

    // For the last block, be careful not to go beyond the end of the buffer
    center = (int)(i * period + 0.5);
    for (j = -width / 2; j < (width + 1) / 2 && shape < shape_end; j++)
        speech[j + center] += ppc_gain * *shape++;
}