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

u32 _s32_to_s9(s32 data)
{
    u32     val;

    if (data > 255)
    {
        data = 255;
    }
    else if (data < -256)
    {
        data = -256;
    }

    val = data & 0x01FF;

    return val;
}