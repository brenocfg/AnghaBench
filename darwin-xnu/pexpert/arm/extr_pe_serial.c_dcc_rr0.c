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
 int ARM_DBGDSCR_RXFULL ; 
 int arm_debug_read_dscr () ; 
 int /*<<< orphan*/  panic_unimplemented () ; 

__attribute__((used)) static int
dcc_rr0(void)
{
#ifdef __arm__
	return arm_debug_read_dscr() & ARM_DBGDSCR_RXFULL;
#else
	/* ARM64_TODO */
	panic_unimplemented();
	return 0;
#endif
}