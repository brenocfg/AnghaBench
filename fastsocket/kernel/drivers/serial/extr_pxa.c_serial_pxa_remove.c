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
struct uart_pxa_port {int /*<<< orphan*/  clk; int /*<<< orphan*/  port; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct uart_pxa_port*) ; 
 struct uart_pxa_port* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  serial_pxa_reg ; 
 int /*<<< orphan*/  uart_remove_one_port (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int serial_pxa_remove(struct platform_device *dev)
{
	struct uart_pxa_port *sport = platform_get_drvdata(dev);

	platform_set_drvdata(dev, NULL);

	uart_remove_one_port(&serial_pxa_reg, &sport->port);
	clk_put(sport->clk);
	kfree(sport);

	return 0;
}