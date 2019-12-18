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
 int /*<<< orphan*/  cnputc (char) ; 
 int /*<<< orphan*/  disableConsoleOutput ; 
 int /*<<< orphan*/  kernel_debugger_entry_count ; 
 int /*<<< orphan*/  log_putc (char) ; 

void
conslog_putc(
	char c)
{
	if (!disableConsoleOutput)
		cnputc(c);

#ifdef	MACH_BSD
	if (!kernel_debugger_entry_count)
		log_putc(c);
#endif
}