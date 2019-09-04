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
typedef  int /*<<< orphan*/  ptrdiff_t ;
typedef  scalar_t__ int16_t ;

/* Variables and functions */
 size_t av_clip_uintp2 (scalar_t__,int) ; 

__attribute__((used)) static void apply_lut(int16_t *buf[3], ptrdiff_t stride,
                      int w, int h, const int16_t *lut)
{
    int y, x, n;

    for (n = 0; n < 3; n++) {
        int16_t *data = buf[n];

        for (y = 0; y < h; y++) {
            for (x = 0; x < w; x++)
                data[x] = lut[av_clip_uintp2(2048 + data[x], 15)];

            data += stride;
        }
    }
}