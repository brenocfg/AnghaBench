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
struct uart_port {int /*<<< orphan*/  lock; scalar_t__ sysrq; } ;
struct console {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 scalar_t__ oops_in_progress ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int spin_trylock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sunhv_console_putchar (struct uart_port*,char) ; 
 struct uart_port* sunhv_port ; 

__attribute__((used)) static void sunhv_console_write_bychar(struct console *con, const char *s, unsigned n)
{
	struct uart_port *port = sunhv_port;
	unsigned long flags;
	int i, locked = 1;

	local_irq_save(flags);
	if (port->sysrq) {
		locked = 0;
	} else if (oops_in_progress) {
		locked = spin_trylock(&port->lock);
	} else
		spin_lock(&port->lock);

	for (i = 0; i < n; i++) {
		if (*s == '\n')
			sunhv_console_putchar(port, '\r');
		sunhv_console_putchar(port, *s++);
	}

	if (locked)
		spin_unlock(&port->lock);
	local_irq_restore(flags);
}