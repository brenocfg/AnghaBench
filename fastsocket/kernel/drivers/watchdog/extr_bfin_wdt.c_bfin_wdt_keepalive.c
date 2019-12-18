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
 int /*<<< orphan*/  bfin_write_WDOG_STAT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stampit () ; 

__attribute__((used)) static int bfin_wdt_keepalive(void)
{
	stampit();
	bfin_write_WDOG_STAT(0);
	return 0;
}