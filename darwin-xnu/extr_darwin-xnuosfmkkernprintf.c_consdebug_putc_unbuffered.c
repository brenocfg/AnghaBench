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
 int /*<<< orphan*/  PE_kputc (char) ; 
 int /*<<< orphan*/  cnputc_unbuffered (char) ; 
 int /*<<< orphan*/  console_is_serial () ; 
 int /*<<< orphan*/  debug_putc (char) ; 
 int /*<<< orphan*/  disableConsoleOutput ; 
 int /*<<< orphan*/  disable_serial_output ; 

void
consdebug_putc_unbuffered(char c)
{
	if (!disableConsoleOutput)
		cnputc_unbuffered(c);

	debug_putc(c);

	if (!console_is_serial() && !disable_serial_output)
			PE_kputc(c);
}