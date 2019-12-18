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

/* Variables and functions */
 unsigned short SCI_CTRL_FLAGS_REIE ; 
 unsigned short SCI_CTRL_FLAGS_RIE ; 
 int /*<<< orphan*/  SCSCR ; 
 unsigned short sci_in (struct uart_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sci_out (struct uart_port*,int /*<<< orphan*/ ,unsigned short) ; 

__attribute__((used)) static void sci_stop_rx(struct uart_port *port)
{
	unsigned short ctrl;

	/* Clear RIE (Receive Interrupt Enable) bit in SCSCR */
	ctrl = sci_in(port, SCSCR);
	ctrl &= ~(SCI_CTRL_FLAGS_RIE | SCI_CTRL_FLAGS_REIE);
	sci_out(port, SCSCR, ctrl);
}