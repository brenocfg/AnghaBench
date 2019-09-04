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
typedef  int /*<<< orphan*/  Palette ;

/* Variables and functions */
 scalar_t__ write_pixel_15_7 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static inline int encode_15_7_sl(Palette * palette, uint8_t * dest,
                                 const uint8_t * src, int width, int dist)
{
    int len = 0, x;
    for (x = 0; x < width; x++) {
        len += write_pixel_15_7(palette, dest + len, src + 3 * x, dist);
    }
    return len;
}