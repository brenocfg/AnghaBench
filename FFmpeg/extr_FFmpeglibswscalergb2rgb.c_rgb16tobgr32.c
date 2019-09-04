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

void rgb16tobgr32(const uint8_t *src, uint8_t *dst, int src_size)
{
    uint8_t *d          = dst;
    const uint16_t *s   = (const uint16_t *)src;
    const uint16_t *end = s + src_size / 2;

    while (s < end) {
        register uint16_t bgr = *s++;
#if HAVE_BIGENDIAN
        *d++ = 255;
        *d++ = ((bgr&0x001F)<<3) | ((bgr&0x001F)>> 2);
        *d++ = ((bgr&0x07E0)>>3) | ((bgr&0x07E0)>> 9);
        *d++ = ((bgr&0xF800)>>8) | ((bgr&0xF800)>>13);
#else
        *d++ = ((bgr&0xF800)>>8) | ((bgr&0xF800)>>13);
        *d++ = ((bgr&0x07E0)>>3) | ((bgr&0x07E0)>> 9);
        *d++ = ((bgr&0x001F)<<3) | ((bgr&0x001F)>> 2);
        *d++ = 255;
#endif
    }
}