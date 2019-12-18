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
typedef  int /*<<< orphan*/  u8_t ;
typedef  size_t u16_t ;
typedef  int /*<<< orphan*/  s32_t ;

/* Variables and functions */
 int /*<<< orphan*/  zfInterpolateFuncX (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

u8_t zfGetInterpolatedValue(u8_t x, u8_t* x_array, u8_t* y_array)
{
    s32_t y;
    u16_t xIndex;

    if (x <= x_array[1])
    {
        xIndex = 0;
    }
    else if (x <= x_array[2])
    {
        xIndex = 1;
    }
    else if (x <= x_array[3])
    {
        xIndex = 2;
    }
    else //(x > x_array[3])
    {
        xIndex = 3;
    }

    y = zfInterpolateFuncX(x,
            x_array[xIndex],
            y_array[xIndex],
            x_array[xIndex+1],
            y_array[xIndex+1]);

    return (u8_t)y;
}