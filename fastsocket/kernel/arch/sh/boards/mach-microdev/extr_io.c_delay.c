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
 int /*<<< orphan*/  ctrl_inw (int) ; 

__attribute__((used)) static inline void delay(void)
{
#if defined(CONFIG_PCI)
	/* System board present, just make a dummy SRAM access.  (CS0 will be
	   mapped to PCI memory, probably good to avoid it.) */
	ctrl_inw(0xa6800000);
#else
	/* CS0 will be mapped to flash, ROM etc so safe to access it. */
	ctrl_inw(0xa0000000);
#endif
}