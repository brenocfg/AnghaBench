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
struct TYPE_7__ {TYPE_2__* tty; int /*<<< orphan*/  flags; } ;
struct TYPE_8__ {TYPE_3__ port; } ;
struct scc_port {TYPE_4__ gs; } ;
struct TYPE_6__ {TYPE_1__* termios; } ;
struct TYPE_5__ {int c_cflag; } ;

/* Variables and functions */
 int /*<<< orphan*/  GS_ACTIVE ; 
 int HUPCL ; 
 int /*<<< orphan*/  scc_setsignals (struct scc_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void scc_shutdown_port(void *ptr)
{
	struct scc_port *port = ptr;

	port->gs.port.flags &= ~ GS_ACTIVE;
	if (port->gs.port.tty && (port->gs.port.tty->termios->c_cflag & HUPCL)) {
		scc_setsignals (port, 0, 0);
	}
}