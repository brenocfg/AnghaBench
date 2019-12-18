#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct tty_struct {TYPE_1__* termios; scalar_t__ driver_data; } ;
struct TYPE_4__ {scalar_t__ head; scalar_t__ tail; scalar_t__ buf; } ;
struct e100_serial {TYPE_2__ xmit; int /*<<< orphan*/  uses_dma_out; int /*<<< orphan*/ * ioport; int /*<<< orphan*/  line; } ;
struct TYPE_3__ {int c_iflag; } ;

/* Variables and functions */
 int /*<<< orphan*/  CIRC_CNT (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DEBUG_LOG (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DFLOW (int /*<<< orphan*/ ) ; 
 unsigned long IO_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned long IO_STATE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int IXON ; 
 size_t REG_XOFF ; 
 int /*<<< orphan*/  R_SERIAL0_XOFF ; 
 int /*<<< orphan*/  SERIAL_XMIT_SIZE ; 
 int /*<<< orphan*/  STOP_CHAR (struct tty_struct*) ; 
 int /*<<< orphan*/  auto_xoff ; 
 int /*<<< orphan*/  e100_enable_serial_tx_ready_irq (struct e100_serial*) ; 
 int /*<<< orphan*/  enable ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  tx_stop ; 
 int /*<<< orphan*/  xoff_char ; 

__attribute__((used)) static void
rs_start(struct tty_struct *tty)
{
	struct e100_serial *info = (struct e100_serial *)tty->driver_data;
	if (info) {
		unsigned long flags;
		unsigned long xoff;

		local_irq_save(flags);
		DFLOW(DEBUG_LOG(info->line, "XOFF rs_start xmit %i\n",
				CIRC_CNT(info->xmit.head,
					 info->xmit.tail,SERIAL_XMIT_SIZE)));
		xoff = IO_FIELD(R_SERIAL0_XOFF, xoff_char, STOP_CHAR(tty));
		xoff |= IO_STATE(R_SERIAL0_XOFF, tx_stop, enable);
		if (tty->termios->c_iflag & IXON ) {
			xoff |= IO_STATE(R_SERIAL0_XOFF, auto_xoff, enable);
		}

		*((unsigned long *)&info->ioport[REG_XOFF]) = xoff;
		if (!info->uses_dma_out &&
		    info->xmit.head != info->xmit.tail && info->xmit.buf)
			e100_enable_serial_tx_ready_irq(info);

		local_irq_restore(flags);
	}
}