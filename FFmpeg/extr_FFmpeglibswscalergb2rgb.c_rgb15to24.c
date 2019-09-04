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

void rgb15to24(const uint8_t *src, uint8_t *dst, int src_size)
{
    uint8_t *d          = dst;
    const uint16_t *s   = (const uint16_t *)src;
    const uint16_t *end = s + src_size / 2;

    while (s < end) {
        register uint16_t bgr = *s++;
        *d++ = ((bgr&0x7C00)>>7) | ((bgr&0x7C00)>>12);
        *d++ = ((bgr&0x03E0)>>2) | ((bgr&0x03E0)>> 7);
        *d++ = ((bgr&0x001F)<<3) | ((bgr&0x001F)>> 2);
    }
}