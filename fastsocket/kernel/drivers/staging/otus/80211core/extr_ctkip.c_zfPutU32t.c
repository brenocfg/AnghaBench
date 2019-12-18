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
typedef  scalar_t__ u8_t ;
typedef  int u32_t ;
typedef  int u16_t ;

/* Variables and functions */

void zfPutU32t(u8_t* p, u32_t value)
{
    u16_t i;

    for(i=0; i<4; i++)
    {
        *p++ = (u8_t) (value & 0xff);
        value >>= 8;
    }
}