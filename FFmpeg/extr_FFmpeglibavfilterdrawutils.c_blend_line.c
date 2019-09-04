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

__attribute__((used)) static void blend_line(uint8_t *dst, unsigned src, unsigned alpha,
                       int dx, int w, unsigned hsub, int left, int right)
{
    unsigned asrc = alpha * src;
    unsigned tau = 0x1010101 - alpha;
    int x;

    if (left) {
        unsigned suba = (left * alpha) >> hsub;
        *dst = (*dst * (0x1010101 - suba) + src * suba) >> 24;
        dst += dx;
    }
    for (x = 0; x < w; x++) {
        *dst = (*dst * tau + asrc) >> 24;
        dst += dx;
    }
    if (right) {
        unsigned suba = (right * alpha) >> hsub;
        *dst = (*dst * (0x1010101 - suba) + src * suba) >> 24;
    }
}