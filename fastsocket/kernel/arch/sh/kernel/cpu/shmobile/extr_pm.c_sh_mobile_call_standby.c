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
 unsigned long ILRAM_BASE ; 

void sh_mobile_call_standby(unsigned long mode)
{
	void *onchip_mem = (void *)ILRAM_BASE;
	void (*standby_onchip_mem)(unsigned long, unsigned long) = onchip_mem;

	/* Let assembly snippet in on-chip memory handle the rest */
	standby_onchip_mem(mode, ILRAM_BASE);
}