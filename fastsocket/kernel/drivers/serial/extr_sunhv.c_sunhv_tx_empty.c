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
 unsigned int TIOCSER_TEMT ; 

__attribute__((used)) static unsigned int sunhv_tx_empty(struct uart_port *port)
{
	/* Transmitter is always empty for us.  If the circ buffer
	 * is non-empty or there is an x_char pending, our caller
	 * will do the right thing and ignore what we return here.
	 */
	return TIOCSER_TEMT;
}