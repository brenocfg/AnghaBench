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
 int ABSY_ASSERTED ; 
 scalar_t__ REG_AUX_STATUS ; 
 int inb (scalar_t__) ; 
 int /*<<< orphan*/  udelay (long) ; 

__attribute__((used)) static int wait_on_busy(unsigned long iobase, unsigned int loop)
{
	while (inb(iobase + REG_AUX_STATUS) & ABSY_ASSERTED) {
		udelay(1L);
		if (--loop == 0)
			return 1;
	}
	return 0;
}