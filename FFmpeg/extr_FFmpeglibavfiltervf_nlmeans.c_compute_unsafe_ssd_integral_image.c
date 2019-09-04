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
typedef  scalar_t__ uint32_t ;
typedef  int ptrdiff_t ;

/* Variables and functions */
 int av_clip (int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void compute_unsafe_ssd_integral_image(uint32_t *dst, ptrdiff_t dst_linesize_32,
                                                     int startx, int starty,
                                                     const uint8_t *src, ptrdiff_t linesize,
                                                     int offx, int offy, int r, int sw, int sh,
                                                     int w, int h)
{
    int x, y;

    for (y = starty; y < starty + h; y++) {
        uint32_t acc = dst[y*dst_linesize_32 + startx - 1] - dst[(y-1)*dst_linesize_32 + startx - 1];
        const int s1y = av_clip(y -  r,         0, sh - 1);
        const int s2y = av_clip(y - (r + offy), 0, sh - 1);

        for (x = startx; x < startx + w; x++) {
            const int s1x = av_clip(x -  r,         0, sw - 1);
            const int s2x = av_clip(x - (r + offx), 0, sw - 1);
            const uint8_t v1 = src[s1y*linesize + s1x];
            const uint8_t v2 = src[s2y*linesize + s2x];
            const int d = v1 - v2;
            acc += d * d;
            dst[y*dst_linesize_32 + x] = dst[(y-1)*dst_linesize_32 + x] + acc;
        }
    }
}