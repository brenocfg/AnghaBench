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
 int TxEmpty ; 
 int /*<<< orphan*/  UART_R_STATUS ; 
 int UR (struct uart_port*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int lh7a40xuart_tx_empty (struct uart_port* port)
{
	return (UR (port, UART_R_STATUS) & TxEmpty) ? TIOCSER_TEMT : 0;
}