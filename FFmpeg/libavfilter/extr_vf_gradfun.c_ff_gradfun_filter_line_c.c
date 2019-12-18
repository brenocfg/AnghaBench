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

/* Variables and functions */
 int FFMAX (int /*<<< orphan*/ ,int) ; 
 int abs (int) ; 
 int av_clip_uint8 (int) ; 

void ff_gradfun_filter_line_c(uint8_t *dst, const uint8_t *src, const uint16_t *dc, int width, int thresh, const uint16_t *dithers)
{
    int x;
    for (x = 0; x < width; dc += x & 1, x++) {
        int pix = src[x] << 7;
        int delta = dc[0] - pix;
        int m = abs(delta) * thresh >> 16;
        m = FFMAX(0, 127 - m);
        m = m * m * delta >> 14;
        pix += m + dithers[x & 7];
        dst[x] = av_clip_uint8(pix >> 7);
    }
}