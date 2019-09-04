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
typedef  int /*<<< orphan*/  ptrdiff_t ;
typedef  int /*<<< orphan*/  int32_t ;
typedef  int /*<<< orphan*/  int16_t ;

/* Variables and functions */

void ff_ivi_put_pixels_8x8(const int32_t *in, int16_t *out, ptrdiff_t pitch,
                           const uint8_t *flags)
{
    int     x, y;

    for (y = 0; y < 8; out += pitch, in += 8, y++)
        for (x = 0; x < 8; x++)
            out[x] = in[x];
}