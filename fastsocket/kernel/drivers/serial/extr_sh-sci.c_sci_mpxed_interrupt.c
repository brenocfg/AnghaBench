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
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_NONE ; 
 unsigned short SCI_CTRL_FLAGS_REIE ; 
 unsigned short SCI_CTRL_FLAGS_RIE ; 
 unsigned short SCI_CTRL_FLAGS_TIE ; 
 int /*<<< orphan*/  SCSCR ; 
 int /*<<< orphan*/  SCxSR ; 
 unsigned short SCxSR_BRK (struct uart_port*) ; 
 unsigned short SCxSR_ERRORS (struct uart_port*) ; 
 unsigned short SCxSR_RDxF (struct uart_port*) ; 
 unsigned short SCxSR_TDxE (struct uart_port*) ; 
 int /*<<< orphan*/  sci_br_interrupt (int,void*) ; 
 int /*<<< orphan*/  sci_er_interrupt (int,void*) ; 
 unsigned short sci_in (struct uart_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sci_rx_interrupt (int,void*) ; 
 int /*<<< orphan*/  sci_tx_interrupt (int,void*) ; 

__attribute__((used)) static irqreturn_t sci_mpxed_interrupt(int irq, void *ptr)
{
	unsigned short ssr_status, scr_status, err_enabled;
	struct uart_port *port = ptr;
	irqreturn_t ret = IRQ_NONE;

	ssr_status = sci_in(port, SCxSR);
	scr_status = sci_in(port, SCSCR);
	err_enabled = scr_status & (SCI_CTRL_FLAGS_REIE | SCI_CTRL_FLAGS_RIE);

	/* Tx Interrupt */
	if ((ssr_status & SCxSR_TDxE(port)) && (scr_status & SCI_CTRL_FLAGS_TIE))
		ret = sci_tx_interrupt(irq, ptr);
	/* Rx Interrupt */
	if ((ssr_status & SCxSR_RDxF(port)) && (scr_status & SCI_CTRL_FLAGS_RIE))
		ret = sci_rx_interrupt(irq, ptr);
	/* Error Interrupt */
	if ((ssr_status & SCxSR_ERRORS(port)) && err_enabled)
		ret = sci_er_interrupt(irq, ptr);
	/* Break Interrupt */
	if ((ssr_status & SCxSR_BRK(port)) && err_enabled)
		ret = sci_br_interrupt(irq, ptr);

	return ret;
}