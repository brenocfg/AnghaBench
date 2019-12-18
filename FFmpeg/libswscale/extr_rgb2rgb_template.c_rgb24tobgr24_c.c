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

__attribute__((used)) static inline void rgb24tobgr24_c(const uint8_t *src, uint8_t *dst, int src_size)
{
    unsigned i;

    for (i = 0; i < src_size; i += 3) {
        register uint8_t x = src[i + 2];
        dst[i + 1]         = src[i + 1];
        dst[i + 2]         = src[i + 0];
        dst[i + 0]         = x;
    }
}