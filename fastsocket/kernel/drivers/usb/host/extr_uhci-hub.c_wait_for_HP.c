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
 int USBPORTSC_CSC ; 
 int inw (unsigned long) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void wait_for_HP(unsigned long port_addr)
{
	int i;

	for (i = 10; i < 250; i += 10) {
		if (inw(port_addr) & USBPORTSC_CSC)
			return;
		udelay(10);
	}
	/* Log a warning? */
}