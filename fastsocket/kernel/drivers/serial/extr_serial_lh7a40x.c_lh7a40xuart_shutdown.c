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
struct uart_port {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT_CLR (struct uart_port*,int /*<<< orphan*/ ,int) ; 
 int BRK ; 
 int FEN ; 
 int UARTEN ; 
 int /*<<< orphan*/  UART_R_CON ; 
 int /*<<< orphan*/  UART_R_FCON ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct uart_port*) ; 

__attribute__((used)) static void lh7a40xuart_shutdown (struct uart_port* port)
{
	free_irq (port->irq, port);
	BIT_CLR (port, UART_R_FCON, BRK | FEN);
	BIT_CLR (port, UART_R_CON, UARTEN);
}