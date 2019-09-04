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
typedef  int int32_t ;

/* Variables and functions */

__attribute__((used)) static inline uint16_t exr_flt2uint(int32_t v)
{
    int32_t exp = v >> 23;
    // "HACK": negative values result in exp<  0, so clipping them to 0
    // is also handled by this condition, avoids explicit check for sign bit.
    if (exp <= 127 + 7 - 24) // we would shift out all bits anyway
        return 0;
    if (exp >= 127)
        return 0xffff;
    v &= 0x007fffff;
    return (v + (1 << 23)) >> (127 + 7 - exp);
}