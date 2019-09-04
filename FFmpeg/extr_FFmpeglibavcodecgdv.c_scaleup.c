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

/* Variables and functions */

__attribute__((used)) static void scaleup(uint8_t *dst, const uint8_t *src, int w)
{
    int x;
    for (x = 0; x < w - 7; x+=8) {
        dst[x + 0] =
        dst[x + 1] = src[(x>>1) + 0];
        dst[x + 2] =
        dst[x + 3] = src[(x>>1) + 1];
        dst[x + 4] =
        dst[x + 5] = src[(x>>1) + 2];
        dst[x + 6] =
        dst[x + 7] = src[(x>>1) + 3];
    }
    for (; x < w; x++) {
        dst[x] = src[(x>>1)];
    }
}