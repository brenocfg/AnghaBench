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
typedef  int int64_t ;

/* Variables and functions */

__attribute__((used)) static uint16_t roundToInt16(int64_t f)
{
    int r = (f + (1 << 15)) >> 16;

    if (r < -0x7FFF)
        return 0x8000;
    else if (r > 0x7FFF)
        return 0x7FFF;
    else
        return r;
}