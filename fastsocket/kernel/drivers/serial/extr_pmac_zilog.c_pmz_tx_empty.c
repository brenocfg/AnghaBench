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
struct uart_pmac_port {int /*<<< orphan*/ * node; } ;

/* Variables and functions */
 unsigned int TIOCSER_TEMT ; 
 unsigned char Tx_BUF_EMP ; 
 scalar_t__ ZS_IS_ASLEEP (struct uart_pmac_port*) ; 
 unsigned char pmz_peek_status (struct uart_pmac_port*) ; 
 struct uart_pmac_port* to_pmz (struct uart_port*) ; 

__attribute__((used)) static unsigned int pmz_tx_empty(struct uart_port *port)
{
	struct uart_pmac_port *uap = to_pmz(port);
	unsigned char status;

	if (ZS_IS_ASLEEP(uap) || uap->node == NULL)
		return TIOCSER_TEMT;

	status = pmz_peek_status(to_pmz(port));
	if (status & Tx_BUF_EMP)
		return TIOCSER_TEMT;
	return 0;
}