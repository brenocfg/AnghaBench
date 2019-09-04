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
typedef  int uint16_t ;
typedef  int int32_t ;

/* Variables and functions */
 size_t BU_IDX ; 
 size_t BV_IDX ; 
 size_t GU_IDX ; 
 size_t GV_IDX ; 
 int RGB2YUV_SHIFT ; 
 size_t RU_IDX ; 
 size_t RV_IDX ; 

__attribute__((used)) static void planar_rgb_to_uv(uint8_t *_dstU, uint8_t *_dstV, const uint8_t *src[4], int width, int32_t *rgb2yuv)
{
    uint16_t *dstU = (uint16_t *)_dstU;
    uint16_t *dstV = (uint16_t *)_dstV;
    int32_t ru = rgb2yuv[RU_IDX], gu = rgb2yuv[GU_IDX], bu = rgb2yuv[BU_IDX];
    int32_t rv = rgb2yuv[RV_IDX], gv = rgb2yuv[GV_IDX], bv = rgb2yuv[BV_IDX];
    int i;
    for (i = 0; i < width; i++) {
        int g = src[0][i];
        int b = src[1][i];
        int r = src[2][i];

        dstU[i] = (ru*r + gu*g + bu*b + (0x4001<<(RGB2YUV_SHIFT-7))) >> (RGB2YUV_SHIFT-6);
        dstV[i] = (rv*r + gv*g + bv*b + (0x4001<<(RGB2YUV_SHIFT-7))) >> (RGB2YUV_SHIFT-6);
    }
}