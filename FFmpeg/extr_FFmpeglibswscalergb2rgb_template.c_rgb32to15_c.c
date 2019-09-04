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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;

/* Variables and functions */

__attribute__((used)) static inline void rgb32to15_c(const uint8_t *src, uint8_t *dst, int src_size)
{
    uint16_t *d        = (uint16_t *)dst;
    const uint8_t *s   = src;
    const uint8_t *end = s + src_size;

    while (s < end) {
        register int rgb  = *(const uint32_t *)s;
        s                += 4;
        *d++              = ((rgb & 0xFF)     >> 3) +
                            ((rgb & 0xF800)   >> 6) +
                            ((rgb & 0xF80000) >> 9);
    }
}