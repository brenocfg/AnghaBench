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
 int WDIOF_CARDRESET ; 
 int /*<<< orphan*/  WDT_CONTROL ; 
 int superio_inb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int it8712f_wdt_get_status(void)
{
	if (superio_inb(WDT_CONTROL) & 0x01)
		return WDIOF_CARDRESET;
	else
		return 0;
}