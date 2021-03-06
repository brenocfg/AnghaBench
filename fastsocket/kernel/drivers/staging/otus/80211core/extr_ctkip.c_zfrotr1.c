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
typedef  int u16_t ;

/* Variables and functions */

u16_t zfrotr1(u16_t a)
// rotate right by 1 bit.
{
    u16_t b;

    if (a & 0x01)
    {
        b = (a >> 1) | 0x8000;
    }
    else
    {
        b = (a >> 1) & 0x7fff;
    }
    return b;
}