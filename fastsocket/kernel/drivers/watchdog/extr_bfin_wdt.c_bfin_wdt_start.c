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
 int ICTL_RESET ; 
 int WDEN_ENABLE ; 
 int /*<<< orphan*/  bfin_write_WDOG_CTL (int) ; 
 int /*<<< orphan*/  stampit () ; 

__attribute__((used)) static int bfin_wdt_start(void)
{
	stampit();
	bfin_write_WDOG_CTL(WDEN_ENABLE | ICTL_RESET);
	return 0;
}