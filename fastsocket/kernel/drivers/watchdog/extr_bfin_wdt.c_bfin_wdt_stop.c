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
 int /*<<< orphan*/  WDEN_DISABLE ; 
 int /*<<< orphan*/  bfin_write_WDOG_CTL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stampit () ; 

__attribute__((used)) static int bfin_wdt_stop(void)
{
	stampit();
	bfin_write_WDOG_CTL(WDEN_DISABLE);
	return 0;
}