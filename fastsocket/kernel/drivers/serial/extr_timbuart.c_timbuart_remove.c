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
struct timbuart_port {int /*<<< orphan*/  port; int /*<<< orphan*/  tasklet; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct timbuart_port*) ; 
 struct timbuart_port* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timbuart_driver ; 
 int /*<<< orphan*/  uart_remove_one_port (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uart_unregister_driver (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int timbuart_remove(struct platform_device *dev)
{
	struct timbuart_port *uart = platform_get_drvdata(dev);

	tasklet_kill(&uart->tasklet);
	uart_remove_one_port(&timbuart_driver, &uart->port);
	uart_unregister_driver(&timbuart_driver);
	kfree(uart);

	return 0;
}