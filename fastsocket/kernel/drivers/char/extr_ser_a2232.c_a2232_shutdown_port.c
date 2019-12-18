#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct a2232status {int Command; int OutFlush; int Setup; } ;
struct TYPE_7__ {TYPE_2__* tty; int /*<<< orphan*/  flags; } ;
struct TYPE_8__ {TYPE_3__ port; } ;
struct a2232_port {TYPE_4__ gs; int /*<<< orphan*/  which_port_on_a2232; int /*<<< orphan*/  which_a2232; } ;
struct TYPE_6__ {TYPE_1__* termios; } ;
struct TYPE_5__ {int c_cflag; } ;

/* Variables and functions */
 int A2232CMD_CMask ; 
 int A2232CMD_Close ; 
 int /*<<< orphan*/  GS_ACTIVE ; 
 int HUPCL ; 
 struct a2232status* a2232stat (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 

__attribute__((used)) static void a2232_shutdown_port(void *ptr)
{
	struct a2232_port *port;
	volatile struct a2232status *stat;
	unsigned long flags;

	port = ptr;
	stat = a2232stat(port->which_a2232, port->which_port_on_a2232);

	local_irq_save(flags);

	port->gs.port.flags &= ~GS_ACTIVE;
	
	if (port->gs.port.tty && port->gs.port.tty->termios->c_cflag & HUPCL) {
		/* Set DTR and RTS to Low, flush output.
		   The NetBSD driver "msc.c" does it this way. */
		stat->Command = (	(stat->Command & ~A2232CMD_CMask) | 
					A2232CMD_Close );
		stat->OutFlush = -1;
		stat->Setup = -1;
	}

	local_irq_restore(flags);
	
	/* After analyzing control flow, I think a2232_shutdown_port
		is actually the last call from the system when at application
		level someone issues a "echo Hello >>/dev/ttyY0".
		Therefore I think the MOD_DEC_USE_COUNT should be here and
		not in "a2232_close()". See the comment in "sx.c", too.
		If you run into problems, compile this driver into the
		kernel instead of compiling it as a module. */
}