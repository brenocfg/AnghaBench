#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct tty_struct {TYPE_3__* termios; scalar_t__ driver_data; } ;
struct TYPE_5__ {int /*<<< orphan*/  tty; } ;
struct TYPE_4__ {int /*<<< orphan*/  tail; int /*<<< orphan*/  head; } ;
struct e100_serial {int /*<<< orphan*/ * ioport; TYPE_2__ port; TYPE_1__ xmit; int /*<<< orphan*/  line; } ;
struct TYPE_6__ {int c_iflag; } ;

/* Variables and functions */
 int /*<<< orphan*/  CIRC_CNT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DEBUG_LOG (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DFLOW (int /*<<< orphan*/ ) ; 
 unsigned long IO_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned long IO_STATE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int IXON ; 
 size_t REG_XOFF ; 
 int /*<<< orphan*/  R_SERIAL0_XOFF ; 
 int /*<<< orphan*/  SERIAL_XMIT_SIZE ; 
 int /*<<< orphan*/  STOP_CHAR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  auto_xoff ; 
 int /*<<< orphan*/  enable ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  stop ; 
 int /*<<< orphan*/  tx_stop ; 
 int /*<<< orphan*/  xoff_char ; 

__attribute__((used)) static void
rs_stop(struct tty_struct *tty)
{
	struct e100_serial *info = (struct e100_serial *)tty->driver_data;
	if (info) {
		unsigned long flags;
		unsigned long xoff;

		local_irq_save(flags);
		DFLOW(DEBUG_LOG(info->line, "XOFF rs_stop xmit %i\n",
				CIRC_CNT(info->xmit.head,
					 info->xmit.tail,SERIAL_XMIT_SIZE)));

		xoff = IO_FIELD(R_SERIAL0_XOFF, xoff_char,
				STOP_CHAR(info->port.tty));
		xoff |= IO_STATE(R_SERIAL0_XOFF, tx_stop, stop);
		if (tty->termios->c_iflag & IXON ) {
			xoff |= IO_STATE(R_SERIAL0_XOFF, auto_xoff, enable);
		}

		*((unsigned long *)&info->ioport[REG_XOFF]) = xoff;
		local_irq_restore(flags);
	}
}