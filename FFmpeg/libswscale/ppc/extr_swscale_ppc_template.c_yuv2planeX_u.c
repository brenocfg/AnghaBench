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
 int av_clip_uint8 (int) ; 

__attribute__((used)) static inline void yuv2planeX_u(const int16_t *filter, int filterSize,
                                const int16_t **src, uint8_t *dest, int dstW,
                                const uint8_t *dither, int offset, int x)
{
    int i, j;

    for (i = x; i < dstW; i++) {
        int t = dither[(i + offset) & 7] << 12;
        for (j = 0; j < filterSize; j++)
            t += src[j][i] * filter[j];
        dest[i] = av_clip_uint8(t >> 19);
    }
}