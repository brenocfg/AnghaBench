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
typedef  int int8_t ;

/* Variables and functions */
 int av_clip_uint8 (int) ; 

void ff_line_noise_c(uint8_t *dst, const uint8_t *src, const int8_t *noise,
                     int len, int shift)
{
    int i;

    noise += shift;
    for (i = 0; i < len; i++) {
        int v = src[i] + noise[i];

        dst[i] = av_clip_uint8(v);
    }
}