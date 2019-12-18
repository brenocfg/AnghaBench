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
struct TYPE_2__ {int flags; int /*<<< orphan*/  tty; } ;
struct gs_port {TYPE_1__ port; } ;

/* Variables and functions */
 int ASYNC_SAK ; 
 int /*<<< orphan*/  TTY_BREAK ; 
 int /*<<< orphan*/  do_SAK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  func_enter () ; 
 int /*<<< orphan*/  func_exit () ; 
 int /*<<< orphan*/  tty_insert_flip_char (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tty_schedule_flip (int /*<<< orphan*/ ) ; 

void gs_got_break(struct gs_port *port)
{
	func_enter ();

	tty_insert_flip_char(port->port.tty, 0, TTY_BREAK);
	tty_schedule_flip(port->port.tty);
	if (port->port.flags & ASYNC_SAK) {
		do_SAK (port->port.tty);
	}

	func_exit ();
}