#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct uart_port {scalar_t__ membase; int /*<<< orphan*/ * dev; } ;
struct platform_device {size_t id; int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {struct uart_port port; } ;

/* Variables and functions */
 scalar_t__ UART_RXFIFO_IRQLEVEL ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 TYPE_1__* netx_ports ; 
 int /*<<< orphan*/  netx_reg ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,TYPE_1__*) ; 
 int /*<<< orphan*/  uart_add_one_port (int /*<<< orphan*/ *,struct uart_port*) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int serial_netx_probe(struct platform_device *pdev)
{
	struct uart_port *port = &netx_ports[pdev->id].port;

	dev_info(&pdev->dev, "initialising\n");

	port->dev = &pdev->dev;

	writel(1, port->membase + UART_RXFIFO_IRQLEVEL);
	uart_add_one_port(&netx_reg, &netx_ports[pdev->id].port);
	platform_set_drvdata(pdev, &netx_ports[pdev->id]);

	return 0;
}