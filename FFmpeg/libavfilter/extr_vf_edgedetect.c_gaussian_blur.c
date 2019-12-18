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
typedef  int /*<<< orphan*/  AVFilterContext ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int*,int const*,int) ; 

__attribute__((used)) static void gaussian_blur(AVFilterContext *ctx, int w, int h,
                                uint8_t *dst, int dst_linesize,
                          const uint8_t *src, int src_linesize)
{
    int i, j;

    memcpy(dst, src, w); dst += dst_linesize; src += src_linesize;
    if (h > 1) {
        memcpy(dst, src, w); dst += dst_linesize; src += src_linesize;
    }
    for (j = 2; j < h - 2; j++) {
        dst[0] = src[0];
        if (w > 1)
            dst[1] = src[1];
        for (i = 2; i < w - 2; i++) {
            /* Gaussian mask of size 5x5 with sigma = 1.4 */
            dst[i] = ((src[-2*src_linesize + i-2] + src[2*src_linesize + i-2]) * 2
                    + (src[-2*src_linesize + i-1] + src[2*src_linesize + i-1]) * 4
                    + (src[-2*src_linesize + i  ] + src[2*src_linesize + i  ]) * 5
                    + (src[-2*src_linesize + i+1] + src[2*src_linesize + i+1]) * 4
                    + (src[-2*src_linesize + i+2] + src[2*src_linesize + i+2]) * 2

                    + (src[  -src_linesize + i-2] + src[  src_linesize + i-2]) *  4
                    + (src[  -src_linesize + i-1] + src[  src_linesize + i-1]) *  9
                    + (src[  -src_linesize + i  ] + src[  src_linesize + i  ]) * 12
                    + (src[  -src_linesize + i+1] + src[  src_linesize + i+1]) *  9
                    + (src[  -src_linesize + i+2] + src[  src_linesize + i+2]) *  4

                    + src[i-2] *  5
                    + src[i-1] * 12
                    + src[i  ] * 15
                    + src[i+1] * 12
                    + src[i+2] *  5) / 159;
        }
        if (w > 2)
            dst[i    ] = src[i    ];
        if (w > 3)
            dst[i + 1] = src[i + 1];

        dst += dst_linesize;
        src += src_linesize;
    }
    if (h > 2) {
        memcpy(dst, src, w); dst += dst_linesize; src += src_linesize;
    }
    if (h > 3)
        memcpy(dst, src, w);
}