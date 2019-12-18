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
typedef  unsigned int uint32_t ;
typedef  unsigned short uint16_t ;

/* Variables and functions */

__attribute__((used)) static inline void rgb15to16_c(const uint8_t *src, uint8_t *dst, int src_size)
{
    register uint8_t *d         = dst;
    register const uint8_t *s   = src;
    register const uint8_t *end = s + src_size;
    const uint8_t *mm_end       = end - 3;

    while (s < mm_end) {
        register unsigned x = *((const uint32_t *)s);
        *((uint32_t *)d)    = (x & 0x7FFF7FFF) + (x & 0x7FE07FE0);
        d += 4;
        s += 4;
    }
    if (s < end) {
        register unsigned short x = *((const uint16_t *)s);
        *((uint16_t *)d)          = (x & 0x7FFF) + (x & 0x7FE0);
    }
}