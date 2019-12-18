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
typedef  int u32 ;
typedef  int s32 ;

/* Variables and functions */

u32 _s32_to_s13(s32 data)
{
    u32     val;

    if (data > 4095)
    {
        data = 4095;
    }
    else if (data < -4096)
    {
        data = -4096;
    }

    val = data & 0x1FFF;

    return val;
}