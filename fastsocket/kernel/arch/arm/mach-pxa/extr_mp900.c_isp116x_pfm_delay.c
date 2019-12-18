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
struct device {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void isp116x_pfm_delay(struct device *dev, int delay)
{

	/* 400Mhz PXA2 = 2.5ns / instruction */

	int cyc = delay / 10;

	/* 4 Instructions = 4 x 2.5ns = 10ns */
	__asm__ volatile ("0:\n"
		"subs %0, %1, #1\n"
		"bge 0b\n"
		:"=r" (cyc)
		:"0"(cyc)
	);
}