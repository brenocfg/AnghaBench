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
struct TYPE_6__ {TYPE_3__* tty; int /*<<< orphan*/  open_wait; } ;
struct TYPE_8__ {TYPE_2__ port; } ;
struct sx_port {int c_dcd; TYPE_4__ gs; } ;
struct TYPE_7__ {TYPE_1__* termios; } ;
struct TYPE_5__ {int c_cflag; } ;

/* Variables and functions */
 int CLOCAL ; 
 int HS_IDLE_CLOSED ; 
 int ST_BREAK ; 
 int ST_DCD ; 
 int /*<<< orphan*/  SX_DEBUG_MODEMSIGNALS ; 
 int /*<<< orphan*/  gs_got_break (TYPE_4__*) ; 
 int hi_hstat ; 
 int /*<<< orphan*/  sx_dprintk (int /*<<< orphan*/ ,char*,...) ; 
 int sx_read_channel_byte (struct sx_port*,int) ; 
 int /*<<< orphan*/  sx_write_channel_byte (struct sx_port*,int,int) ; 
 int /*<<< orphan*/  tty_hangup (TYPE_3__*) ; 
 int tty_port_carrier_raised (TYPE_2__*) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void sx_check_modem_signals(struct sx_port *port)
{
	int hi_state;
	int c_dcd;

	hi_state = sx_read_channel_byte(port, hi_state);
	sx_dprintk(SX_DEBUG_MODEMSIGNALS, "Checking modem signals (%d/%d)\n",
			port->c_dcd, tty_port_carrier_raised(&port->gs.port));

	if (hi_state & ST_BREAK) {
		hi_state &= ~ST_BREAK;
		sx_dprintk(SX_DEBUG_MODEMSIGNALS, "got a break.\n");
		sx_write_channel_byte(port, hi_state, hi_state);
		gs_got_break(&port->gs);
	}
	if (hi_state & ST_DCD) {
		hi_state &= ~ST_DCD;
		sx_dprintk(SX_DEBUG_MODEMSIGNALS, "got a DCD change.\n");
		sx_write_channel_byte(port, hi_state, hi_state);
		c_dcd = tty_port_carrier_raised(&port->gs.port);
		sx_dprintk(SX_DEBUG_MODEMSIGNALS, "DCD is now %d\n", c_dcd);
		if (c_dcd != port->c_dcd) {
			port->c_dcd = c_dcd;
			if (tty_port_carrier_raised(&port->gs.port)) {
				/* DCD went UP */
				if ((sx_read_channel_byte(port, hi_hstat) !=
						HS_IDLE_CLOSED) &&
						!(port->gs.port.tty->termios->
							c_cflag & CLOCAL)) {
					/* Are we blocking in open? */
					sx_dprintk(SX_DEBUG_MODEMSIGNALS, "DCD "
						"active, unblocking open\n");
					wake_up_interruptible(&port->gs.port.
							open_wait);
				} else {
					sx_dprintk(SX_DEBUG_MODEMSIGNALS, "DCD "
						"raised. Ignoring.\n");
				}
			} else {
				/* DCD went down! */
				if (!(port->gs.port.tty->termios->c_cflag & CLOCAL)){
					sx_dprintk(SX_DEBUG_MODEMSIGNALS, "DCD "
						"dropped. hanging up....\n");
					tty_hangup(port->gs.port.tty);
				} else {
					sx_dprintk(SX_DEBUG_MODEMSIGNALS, "DCD "
						"dropped. ignoring.\n");
				}
			}
		} else {
			sx_dprintk(SX_DEBUG_MODEMSIGNALS, "Hmmm. card told us "
				"DCD changed, but it didn't.\n");
		}
	}
}