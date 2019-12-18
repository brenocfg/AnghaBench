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
struct TYPE_2__ {int /*<<< orphan*/  membase; } ;
struct uart_amba_port {int /*<<< orphan*/  clk; TYPE_1__ port; } ;
struct amba_device {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct uart_amba_port**) ; 
 struct uart_amba_port* amba_get_drvdata (struct amba_device*) ; 
 struct uart_amba_port** amba_ports ; 
 int /*<<< orphan*/  amba_reg ; 
 int /*<<< orphan*/  amba_set_drvdata (struct amba_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clk_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct uart_amba_port*) ; 
 int /*<<< orphan*/  uart_remove_one_port (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static int pl010_remove(struct amba_device *dev)
{
	struct uart_amba_port *uap = amba_get_drvdata(dev);
	int i;

	amba_set_drvdata(dev, NULL);

	uart_remove_one_port(&amba_reg, &uap->port);

	for (i = 0; i < ARRAY_SIZE(amba_ports); i++)
		if (amba_ports[i] == uap)
			amba_ports[i] = NULL;

	iounmap(uap->port.membase);
	clk_put(uap->clk);
	kfree(uap);
	return 0;
}