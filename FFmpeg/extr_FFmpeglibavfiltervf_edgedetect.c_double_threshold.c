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

/* Variables and functions */

__attribute__((used)) static void double_threshold(int low, int high, int w, int h,
                                   uint8_t *dst, int dst_linesize,
                             const uint8_t *src, int src_linesize)
{
    int i, j;

    for (j = 0; j < h; j++) {
        for (i = 0; i < w; i++) {
            if (src[i] > high) {
                dst[i] = src[i];
                continue;
            }

            if ((!i || i == w - 1 || !j || j == h - 1) &&
                src[i] > low &&
                (src[-src_linesize + i-1] > high ||
                 src[-src_linesize + i  ] > high ||
                 src[-src_linesize + i+1] > high ||
                 src[                i-1] > high ||
                 src[                i+1] > high ||
                 src[ src_linesize + i-1] > high ||
                 src[ src_linesize + i  ] > high ||
                 src[ src_linesize + i+1] > high))
                dst[i] = src[i];
            else
                dst[i] = 0;
        }
        dst += dst_linesize;
        src += src_linesize;
    }
}