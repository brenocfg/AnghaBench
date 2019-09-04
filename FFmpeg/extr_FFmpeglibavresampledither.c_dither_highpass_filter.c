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
 float SQRT_1_6 ; 

__attribute__((used)) static void dither_highpass_filter(float *src, int len)
{
    int i;

    /* filter is from libswresample in FFmpeg */
    for (i = 0; i < len - 2; i++)
        src[i] = (-src[i] + 2 * src[i + 1] - src[i + 2]) * SQRT_1_6;
}