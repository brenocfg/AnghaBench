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
typedef  scalar_t__ s32_t ;

/* Variables and functions */

s32_t zfInterpolateFunc(s32_t x, s32_t x1, s32_t y1, s32_t x2, s32_t y2)
{
    s32_t y;

    if (y2 == y1)
    {
        y = y1;
    }
    else if (x == x1)
    {
        y = y1;
    }
    else if (x == x2)
    {
        y = y2;
    }
    else if (x2 != x1)
    {
        y = y1 + (((y2-y1) * (x-x1))/(x2-x1));
    }
    else
    {
        y = y1;
    }

    return y;
}