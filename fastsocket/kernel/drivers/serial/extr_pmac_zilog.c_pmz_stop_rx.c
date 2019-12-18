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
struct uart_port {int dummy; } ;
struct uart_pmac_port {int /*<<< orphan*/ * curregs; int /*<<< orphan*/ * node; } ;

/* Variables and functions */
 size_t R1 ; 
 int /*<<< orphan*/  RxINT_MASK ; 
 scalar_t__ ZS_IS_ASLEEP (struct uart_pmac_port*) ; 
 int /*<<< orphan*/  pmz_debug (char*) ; 
 int /*<<< orphan*/  pmz_maybe_update_regs (struct uart_pmac_port*) ; 
 struct uart_pmac_port* to_pmz (struct uart_port*) ; 

__attribute__((used)) static void pmz_stop_rx(struct uart_port *port)
{
	struct uart_pmac_port *uap = to_pmz(port);

	if (ZS_IS_ASLEEP(uap) || uap->node == NULL)
		return;

	pmz_debug("pmz: stop_rx()()\n");

	/* Disable all RX interrupts.  */
	uap->curregs[R1] &= ~RxINT_MASK;
	pmz_maybe_update_regs(uap);

	pmz_debug("pmz: stop_rx() done.\n");
}