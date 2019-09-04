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

/* Variables and functions */
 int MAX_NEG_CROP ; 
 int* ff_crop_tab ; 

__attribute__((used)) static void wmv2_mspel8_h_lowpass(uint8_t *dst, const uint8_t *src,
                                  int dstStride, int srcStride, int h)
{
    const uint8_t *cm = ff_crop_tab + MAX_NEG_CROP;
    int i;

    for (i = 0; i < h; i++) {
        dst[0] = cm[(9 * (src[0] + src[1]) - (src[-1] + src[2]) + 8) >> 4];
        dst[1] = cm[(9 * (src[1] + src[2]) - (src[0]  + src[3]) + 8) >> 4];
        dst[2] = cm[(9 * (src[2] + src[3]) - (src[1]  + src[4]) + 8) >> 4];
        dst[3] = cm[(9 * (src[3] + src[4]) - (src[2]  + src[5]) + 8) >> 4];
        dst[4] = cm[(9 * (src[4] + src[5]) - (src[3]  + src[6]) + 8) >> 4];
        dst[5] = cm[(9 * (src[5] + src[6]) - (src[4]  + src[7]) + 8) >> 4];
        dst[6] = cm[(9 * (src[6] + src[7]) - (src[5]  + src[8]) + 8) >> 4];
        dst[7] = cm[(9 * (src[7] + src[8]) - (src[6]  + src[9]) + 8) >> 4];
        dst   += dstStride;
        src   += srcStride;
    }
}