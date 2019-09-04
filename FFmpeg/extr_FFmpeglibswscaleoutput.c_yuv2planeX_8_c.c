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

__attribute__((used)) static void yuv2planeX_8_c(const int16_t *filter, int filterSize,
                           const int16_t **src, uint8_t *dest, int dstW,
                           const uint8_t *dither, int offset)
{
    int i;
    for (i=0; i<dstW; i++) {
        int val = dither[(i + offset) & 7] << 12;
        int j;
        for (j=0; j<filterSize; j++)
            val += src[j][i] * filter[j];

        dest[i]= av_clip_uint8(val>>19);
    }
}