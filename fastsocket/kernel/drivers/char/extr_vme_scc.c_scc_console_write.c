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
struct console {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  scc_ch_write (char) ; 

__attribute__((used)) static void scc_console_write (struct console *co, const char *str, unsigned count)
{
	unsigned long	flags;

	local_irq_save(flags);

	while (count--)
	{
		if (*str == '\n')
			scc_ch_write ('\r');
		scc_ch_write (*str++);
	}
	local_irq_restore(flags);
}