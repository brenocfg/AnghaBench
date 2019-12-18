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
 int IO_FIELD (int*,int /*<<< orphan*/ ,int) ; 
 int IO_STATE (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int* R_WATCHDOG ; 
 int /*<<< orphan*/  enable ; 
 int /*<<< orphan*/  key ; 
 int /*<<< orphan*/  stop ; 
 int watchdog_key ; 

void 
stop_watchdog(void)
{
#if defined(CONFIG_ETRAX_WATCHDOG) && !defined(CONFIG_SVINTO_SIM)
	watchdog_key ^= 0x7; /* invert key, which is 3 bits */
	*R_WATCHDOG = IO_FIELD(R_WATCHDOG, key, watchdog_key) |
		IO_STATE(R_WATCHDOG, enable, stop);
#endif	
}