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

/* Variables and functions */

void rgb12to15(const uint8_t *src, uint8_t *dst, int src_size)
{
    uint16_t rgb, r, g, b;
    uint16_t *d         = (uint16_t *)dst;
    const uint16_t *s   = (const uint16_t *)src;
    const uint16_t *end = s + src_size / 2;

    while (s < end) {
        rgb  = *s++;
        r    = rgb & 0xF00;
        g    = rgb & 0x0F0;
        b    = rgb & 0x00F;
        r    = (r << 3) | ((r & 0x800) >> 1);
        g    = (g << 2) | ((g & 0x080) >> 2);
        b    = (b << 1) | ( b          >> 3);
        *d++ = r | g | b;
    }
}