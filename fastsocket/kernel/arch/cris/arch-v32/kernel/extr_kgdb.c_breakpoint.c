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
 scalar_t__ dynamic_bp ; 
 int kgdb_started ; 

void
breakpoint(void)
{
	kgdb_started = 1;
	dynamic_bp = 0;     /* This is a static, not a dynamic breakpoint. */
	__asm__ volatile ("break 8"); /* Jump to kgdb_handle_breakpoint. */
}