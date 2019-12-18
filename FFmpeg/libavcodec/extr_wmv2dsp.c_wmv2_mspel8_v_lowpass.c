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

__attribute__((used)) static void wmv2_mspel8_v_lowpass(uint8_t *dst, const uint8_t *src,
                                  int dstStride, int srcStride, int w)
{
    const uint8_t *cm = ff_crop_tab + MAX_NEG_CROP;
    int i;

    for (i = 0; i < w; i++) {
        const int src_1 = src[-srcStride];
        const int src0  = src[0];
        const int src1  = src[srcStride];
        const int src2  = src[2 * srcStride];
        const int src3  = src[3 * srcStride];
        const int src4  = src[4 * srcStride];
        const int src5  = src[5 * srcStride];
        const int src6  = src[6 * srcStride];
        const int src7  = src[7 * srcStride];
        const int src8  = src[8 * srcStride];
        const int src9  = src[9 * srcStride];
        dst[0 * dstStride] = cm[(9 * (src0 + src1) - (src_1 + src2) + 8) >> 4];
        dst[1 * dstStride] = cm[(9 * (src1 + src2) - (src0  + src3) + 8) >> 4];
        dst[2 * dstStride] = cm[(9 * (src2 + src3) - (src1  + src4) + 8) >> 4];
        dst[3 * dstStride] = cm[(9 * (src3 + src4) - (src2  + src5) + 8) >> 4];
        dst[4 * dstStride] = cm[(9 * (src4 + src5) - (src3  + src6) + 8) >> 4];
        dst[5 * dstStride] = cm[(9 * (src5 + src6) - (src4  + src7) + 8) >> 4];
        dst[6 * dstStride] = cm[(9 * (src6 + src7) - (src5  + src8) + 8) >> 4];
        dst[7 * dstStride] = cm[(9 * (src7 + src8) - (src6  + src9) + 8) >> 4];
        src++;
        dst++;
    }
}