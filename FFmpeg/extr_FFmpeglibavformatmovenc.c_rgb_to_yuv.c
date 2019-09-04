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
typedef  int rgb ;

/* Variables and functions */
 int av_clip_uint8 (int) ; 

__attribute__((used)) static uint32_t rgb_to_yuv(uint32_t rgb)
{
    uint8_t r, g, b;
    int y, cb, cr;

    r = (rgb >> 16) & 0xFF;
    g = (rgb >>  8) & 0xFF;
    b = (rgb      ) & 0xFF;

    y  = av_clip_uint8(( 16000 +  257 * r + 504 * g +  98 * b)/1000);
    cb = av_clip_uint8((128000 -  148 * r - 291 * g + 439 * b)/1000);
    cr = av_clip_uint8((128000 +  439 * r - 368 * g -  71 * b)/1000);

    return (y << 16) | (cr << 8) | cb;
}