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
typedef  int int64_t ;

/* Variables and functions */
 int FFMIN (int,int) ; 
 int av_clip (int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static uint8_t *interpolate_bilinear8(uint8_t *dst_color,
                                      const uint8_t *src, int src_linesize, int src_linestep,
                                      int x, int y, int max_x, int max_y)
{
    int int_x = av_clip(x>>16, 0, max_x);
    int int_y = av_clip(y>>16, 0, max_y);
    int frac_x = x&0xFFFF;
    int frac_y = y&0xFFFF;
    int i;
    int int_x1 = FFMIN(int_x+1, max_x);
    int int_y1 = FFMIN(int_y+1, max_y);

    for (i = 0; i < src_linestep; i++) {
        int s00 = src[src_linestep * int_x  + i + src_linesize * int_y ];
        int s01 = src[src_linestep * int_x1 + i + src_linesize * int_y ];
        int s10 = src[src_linestep * int_x  + i + src_linesize * int_y1];
        int s11 = src[src_linestep * int_x1 + i + src_linesize * int_y1];
        int s0 = (((1<<16) - frac_x)*s00 + frac_x*s01);
        int s1 = (((1<<16) - frac_x)*s10 + frac_x*s11);

        dst_color[i] = ((int64_t)((1<<16) - frac_y)*s0 + (int64_t)frac_y*s1) >> 32;
    }

    return dst_color;
}