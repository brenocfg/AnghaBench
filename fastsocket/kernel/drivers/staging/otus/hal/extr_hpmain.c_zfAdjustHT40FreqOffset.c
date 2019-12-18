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
typedef  int /*<<< orphan*/  zdev_t ;
typedef  int u8_t ;
typedef  int u32_t ;

/* Variables and functions */

u32_t zfAdjustHT40FreqOffset(zdev_t* dev, u32_t frequency, u8_t bw40, u8_t extOffset)
{
    u32_t newFreq = frequency;

	if (bw40 == 1)
	{
        if (extOffset == 1)
        {
            newFreq += 10;
        }
        else
        {
            newFreq -= 10;
        }
	}
	return newFreq;
}