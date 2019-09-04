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
typedef  unsigned int uint8_t ;
typedef  unsigned int int32_t ;

/* Variables and functions */
 size_t BU_IDX ; 
 size_t BV_IDX ; 
 size_t BY_IDX ; 
 size_t GU_IDX ; 
 size_t GV_IDX ; 
 size_t GY_IDX ; 
 unsigned int RGB2YUV_SHIFT ; 
 size_t RU_IDX ; 
 size_t RV_IDX ; 
 size_t RY_IDX ; 

void ff_rgb24toyv12_c(const uint8_t *src, uint8_t *ydst, uint8_t *udst,
                   uint8_t *vdst, int width, int height, int lumStride,
                   int chromStride, int srcStride, int32_t *rgb2yuv)
{
    int32_t ry = rgb2yuv[RY_IDX], gy = rgb2yuv[GY_IDX], by = rgb2yuv[BY_IDX];
    int32_t ru = rgb2yuv[RU_IDX], gu = rgb2yuv[GU_IDX], bu = rgb2yuv[BU_IDX];
    int32_t rv = rgb2yuv[RV_IDX], gv = rgb2yuv[GV_IDX], bv = rgb2yuv[BV_IDX];
    int y;
    const int chromWidth = width >> 1;

    for (y = 0; y < height; y += 2) {
        int i;
        for (i = 0; i < chromWidth; i++) {
            unsigned int b = src[6 * i + 0];
            unsigned int g = src[6 * i + 1];
            unsigned int r = src[6 * i + 2];

            unsigned int Y = ((ry * r + gy * g + by * b) >> RGB2YUV_SHIFT) +  16;
            unsigned int V = ((rv * r + gv * g + bv * b) >> RGB2YUV_SHIFT) + 128;
            unsigned int U = ((ru * r + gu * g + bu * b) >> RGB2YUV_SHIFT) + 128;

            udst[i]     = U;
            vdst[i]     = V;
            ydst[2 * i] = Y;

            b = src[6 * i + 3];
            g = src[6 * i + 4];
            r = src[6 * i + 5];

            Y = ((ry * r + gy * g + by * b) >> RGB2YUV_SHIFT) + 16;
            ydst[2 * i + 1] = Y;
        }
        ydst += lumStride;
        src  += srcStride;

        if (y+1 == height)
            break;

        for (i = 0; i < chromWidth; i++) {
            unsigned int b = src[6 * i + 0];
            unsigned int g = src[6 * i + 1];
            unsigned int r = src[6 * i + 2];

            unsigned int Y = ((ry * r + gy * g + by * b) >> RGB2YUV_SHIFT) + 16;

            ydst[2 * i] = Y;

            b = src[6 * i + 3];
            g = src[6 * i + 4];
            r = src[6 * i + 5];

            Y = ((ry * r + gy * g + by * b) >> RGB2YUV_SHIFT) + 16;
            ydst[2 * i + 1] = Y;
        }
        udst += chromStride;
        vdst += chromStride;
        ydst += lumStride;
        src  += srcStride;
    }
}