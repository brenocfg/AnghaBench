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
 int READ_SC_PORT (struct uart_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SR ; 
 int SR_TXRDY ; 
 unsigned int TIOCSER_TEMT ; 

__attribute__((used)) static unsigned int sc26xx_tx_empty(struct uart_port *port)
{
	return (READ_SC_PORT(port, SR) & SR_TXRDY) ? TIOCSER_TEMT : 0;
}