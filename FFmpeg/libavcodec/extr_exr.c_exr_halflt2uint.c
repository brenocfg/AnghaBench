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
typedef  int uint16_t ;

/* Variables and functions */

__attribute__((used)) static inline uint16_t exr_halflt2uint(uint16_t v)
{
    unsigned exp = 14 - (v >> 10);
    if (exp >= 14) {
        if (exp == 14)
            return (v >> 9) & 1;
        else
            return (v & 0x8000) ? 0 : 0xffff;
    }
    v <<= 6;
    return (v + (1 << 16)) >> (exp + 1);
}