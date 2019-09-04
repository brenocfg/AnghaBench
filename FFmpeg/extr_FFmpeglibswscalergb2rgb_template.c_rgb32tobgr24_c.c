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

__attribute__((used)) static inline void rgb32tobgr24_c(const uint8_t *src, uint8_t *dst,
                                  int src_size)
{
    uint8_t *dest      = dst;
    const uint8_t *s   = src;
    const uint8_t *end = s + src_size;

    while (s < end) {
#if HAVE_BIGENDIAN
        /* RGB32 (= A, B, G, R) -> RGB24 (= R, G, B) */
        s++;
        dest[2]  = *s++;
        dest[1]  = *s++;
        dest[0]  = *s++;
        dest    += 3;
#else
        *dest++  = *s++;
        *dest++  = *s++;
        *dest++  = *s++;
        s++;
#endif
    }
}