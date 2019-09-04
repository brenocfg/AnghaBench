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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint16_t ;
typedef  scalar_t__ int16_t ;

/* Variables and functions */
 int /*<<< orphan*/  av_clip_uint8 (scalar_t__ const) ; 

__attribute__((used)) static void add_rect_clamped_c(uint8_t *dst, const uint16_t *src, int stride,
                               const int16_t *idwt, int idwt_stride,
                               int width, int height)
{
    int x, y;

    for (y = 0; y < height; y++) {
        for (x = 0; x < width; x+=2) {
            dst[x  ] = av_clip_uint8(((src[x  ]+32)>>6) + idwt[x  ]);
            dst[x+1] = av_clip_uint8(((src[x+1]+32)>>6) + idwt[x+1]);
        }
        dst += stride;
        src += stride;
        idwt += idwt_stride;
    }
}