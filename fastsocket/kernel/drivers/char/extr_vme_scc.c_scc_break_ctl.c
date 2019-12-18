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
struct tty_struct {struct scc_port* driver_data; } ;
struct scc_port {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCC_ACCESS_INIT (struct scc_port*) ; 
 int /*<<< orphan*/  SCCmod (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TCR_SEND_BREAK ; 
 int /*<<< orphan*/  TX_CTRL_REG ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 

__attribute__((used)) static int scc_break_ctl(struct tty_struct *tty, int break_state)
{
	struct scc_port *port = tty->driver_data;
	unsigned long	flags;
	SCC_ACCESS_INIT(port);

	local_irq_save(flags);
	SCCmod(TX_CTRL_REG, ~TCR_SEND_BREAK, 
			break_state ? TCR_SEND_BREAK : 0);
	local_irq_restore(flags);
	return 0;
}