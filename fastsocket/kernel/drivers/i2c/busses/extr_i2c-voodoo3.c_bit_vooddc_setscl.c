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
 unsigned int DDC_SCL_OUT ; 
 scalar_t__ REG ; 
 scalar_t__ ioaddr ; 
 unsigned int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (unsigned int,scalar_t__) ; 

__attribute__((used)) static void bit_vooddc_setscl(void *data, int val)
{
	unsigned int r;
	r = readl(ioaddr + REG);
	if (val)
		r |= DDC_SCL_OUT;
	else
		r &= ~DDC_SCL_OUT;
	writel(r, ioaddr + REG);
	readl(ioaddr + REG);	/* flush posted write */
}