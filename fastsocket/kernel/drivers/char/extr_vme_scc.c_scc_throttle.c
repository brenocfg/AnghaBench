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
struct tty_struct {TYPE_1__* termios; struct scc_port* driver_data; } ;
struct scc_port {int dummy; } ;
struct TYPE_2__ {int c_cflag; } ;

/* Variables and functions */
 int CRTSCTS ; 
 scalar_t__ I_IXOFF (struct tty_struct*) ; 
 int /*<<< orphan*/  SCC_ACCESS_INIT (struct scc_port*) ; 
 int /*<<< orphan*/  SCCmod (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STOP_CHAR (struct tty_struct*) ; 
 int /*<<< orphan*/  TCR_RTS ; 
 int /*<<< orphan*/  TX_CTRL_REG ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  scc_send_xchar (struct tty_struct*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void scc_throttle (struct tty_struct * tty)
{
	struct scc_port *port = tty->driver_data;
	unsigned long	flags;
	SCC_ACCESS_INIT(port);

	if (tty->termios->c_cflag & CRTSCTS) {
		local_irq_save(flags);
		SCCmod(TX_CTRL_REG, ~TCR_RTS, 0);
		local_irq_restore(flags);
	}
	if (I_IXOFF(tty))
		scc_send_xchar(tty, STOP_CHAR(tty));
}