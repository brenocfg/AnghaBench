#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct console {int dummy; } ;
struct TYPE_2__ {int* read; char* write; } ;

/* Variables and functions */
 int IO_MASK (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  R_SERIAL0_READ ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 TYPE_1__* port ; 
 int /*<<< orphan*/  reset_watchdog () ; 
 int /*<<< orphan*/  tr_ready ; 

__attribute__((used)) static void
console_write_direct(struct console *co, const char *buf, unsigned int len)
{
	int i;
	unsigned long flags;

        if (!port)
		return;

	local_irq_save(flags);

	/* Send data */
	for (i = 0; i < len; i++) {
		/* LF -> CRLF */
		if (buf[i] == '\n') {
			while (!(*port->read & IO_MASK(R_SERIAL0_READ, tr_ready)))
			;
			*port->write = '\r';
		}
		/* Wait until transmitter is ready and send.*/
		while (!(*port->read & IO_MASK(R_SERIAL0_READ, tr_ready)))
			;
		*port->write = buf[i];
	}

	/*
	 * Feed the watchdog, otherwise it will reset the chip during boot.
	 * The time to send an ordinary boot message line (10-90 chars)
	 * varies between 1-8ms at 115200. What makes up for the additional
	 * 90ms that allows the watchdog to bite?
	*/
	reset_watchdog();

	local_irq_restore(flags);
}