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
struct uart_amba_port {int /*<<< orphan*/  port; } ;
struct amba_device {int dummy; } ;
typedef  int /*<<< orphan*/  pm_message_t ;

/* Variables and functions */
 struct uart_amba_port* amba_get_drvdata (struct amba_device*) ; 
 int /*<<< orphan*/  amba_reg ; 
 int /*<<< orphan*/  uart_suspend_port (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pl010_suspend(struct amba_device *dev, pm_message_t state)
{
	struct uart_amba_port *uap = amba_get_drvdata(dev);

	if (uap)
		uart_suspend_port(&amba_reg, &uap->port);

	return 0;
}