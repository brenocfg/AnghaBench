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

/* Variables and functions */
 int /*<<< orphan*/  Sleep (int) ; 
 unsigned int plat_get_ticks_us () ; 

void plat_wait_till_us(unsigned int us)
{
	int msdiff = (int)(us - plat_get_ticks_us()) / 1000;
	if (msdiff > 6)
		Sleep(msdiff - 6);
	while (plat_get_ticks_us() < us)
		;
}