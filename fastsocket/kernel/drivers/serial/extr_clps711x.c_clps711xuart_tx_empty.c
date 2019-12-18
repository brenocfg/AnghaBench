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
 int /*<<< orphan*/  SYSFLG (struct uart_port*) ; 
 unsigned int SYSFLG_UBUSY ; 
 unsigned int TIOCSER_TEMT ; 
 unsigned int clps_readl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int clps711xuart_tx_empty(struct uart_port *port)
{
	unsigned int status = clps_readl(SYSFLG(port));
	return status & SYSFLG_UBUSY ? 0 : TIOCSER_TEMT;
}