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
typedef  float uint8_t ;
typedef  int /*<<< orphan*/  ptrdiff_t ;
typedef  int /*<<< orphan*/  AVFilterContext ;

/* Variables and functions */
 float av_clip_uint8 (float const) ; 

__attribute__((used)) static int deflicker8(AVFilterContext *ctx,
                      const uint8_t *src, ptrdiff_t src_linesize,
                      uint8_t *dst, ptrdiff_t dst_linesize,
                      int w, int h, float f)
{
    int x, y;

    for (y = 0; y < h; y++) {
        for (x = 0; x < w; x++) {
            dst[x] = av_clip_uint8(src[x] * f);
        }

        dst += dst_linesize;
        src += src_linesize;
    }

    return 0;
}