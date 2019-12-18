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
typedef  int u32 ;
struct uart_port {scalar_t__ membase; } ;

/* Variables and functions */
 scalar_t__ TIMBUART_IER ; 
 int TXBAE ; 
 int ioread32 (scalar_t__) ; 
 int /*<<< orphan*/  iowrite32 (int,scalar_t__) ; 

__attribute__((used)) static void timbuart_stop_tx(struct uart_port *port)
{
	/* spinlock held by upper layer, disable TX interrupt */
	u32 ier = ioread32(port->membase + TIMBUART_IER) & ~TXBAE;
	iowrite32(ier, port->membase + TIMBUART_IER);
}