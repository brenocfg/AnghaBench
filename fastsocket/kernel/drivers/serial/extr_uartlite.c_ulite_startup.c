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
struct uart_port {scalar_t__ membase; int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int IRQF_SAMPLE_RANDOM ; 
 int IRQF_SHARED ; 
 scalar_t__ ULITE_CONTROL ; 
 int ULITE_CONTROL_IE ; 
 int ULITE_CONTROL_RST_RX ; 
 int ULITE_CONTROL_RST_TX ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,struct uart_port*) ; 
 int /*<<< orphan*/  ulite_isr ; 
 int /*<<< orphan*/  writeb (int,scalar_t__) ; 

__attribute__((used)) static int ulite_startup(struct uart_port *port)
{
	int ret;

	ret = request_irq(port->irq, ulite_isr,
			  IRQF_SHARED | IRQF_SAMPLE_RANDOM, "uartlite", port);
	if (ret)
		return ret;

	writeb(ULITE_CONTROL_RST_RX | ULITE_CONTROL_RST_TX,
	       port->membase + ULITE_CONTROL);
	writeb(ULITE_CONTROL_IE, port->membase + ULITE_CONTROL);

	return 0;
}