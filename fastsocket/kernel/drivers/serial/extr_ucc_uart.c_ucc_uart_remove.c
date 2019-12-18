#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  line; } ;
struct uart_qe_port {TYPE_1__ port; } ;
struct of_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 struct uart_qe_port* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct uart_qe_port*) ; 
 int /*<<< orphan*/  uart_remove_one_port (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  ucc_uart_driver ; 

__attribute__((used)) static int ucc_uart_remove(struct of_device *ofdev)
{
	struct uart_qe_port *qe_port = dev_get_drvdata(&ofdev->dev);

	dev_info(&ofdev->dev, "removing /dev/ttyQE%u\n", qe_port->port.line);

	uart_remove_one_port(&ucc_uart_driver, &qe_port->port);

	dev_set_drvdata(&ofdev->dev, NULL);
	kfree(qe_port);

	return 0;
}