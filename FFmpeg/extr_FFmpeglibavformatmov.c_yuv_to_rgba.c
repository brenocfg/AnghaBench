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
typedef  int uint32_t ;

/* Variables and functions */
 int av_clip_uint8 (int) ; 

__attribute__((used)) static uint32_t yuv_to_rgba(uint32_t ycbcr)
{
    uint8_t r, g, b;
    int y, cb, cr;

    y  = (ycbcr >> 16) & 0xFF;
    cr = (ycbcr >> 8)  & 0xFF;
    cb =  ycbcr        & 0xFF;

    b = av_clip_uint8((1164 * (y - 16)                     + 2018 * (cb - 128)) / 1000);
    g = av_clip_uint8((1164 * (y - 16) -  813 * (cr - 128) -  391 * (cb - 128)) / 1000);
    r = av_clip_uint8((1164 * (y - 16) + 1596 * (cr - 128)                    ) / 1000);

    return (r << 16) | (g << 8) | b;
}