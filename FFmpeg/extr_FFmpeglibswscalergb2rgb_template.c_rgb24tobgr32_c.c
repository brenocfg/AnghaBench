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

__attribute__((used)) static inline void rgb24tobgr32_c(const uint8_t *src, uint8_t *dst,
                                  int src_size)
{
    uint8_t *dest      = dst;
    const uint8_t *s   = src;
    const uint8_t *end = s + src_size;

    while (s < end) {
#if HAVE_BIGENDIAN
        /* RGB24 (= R, G, B) -> RGB32 (= A, B, G, R) */
        *dest++  = 255;
        *dest++  = s[2];
        *dest++  = s[1];
        *dest++  = s[0];
        s       += 3;
#else
        *dest++  = *s++;
        *dest++  = *s++;
        *dest++  = *s++;
        *dest++  = 255;
#endif
    }
}