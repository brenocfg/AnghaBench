#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {struct imxuart_platform_data* platform_data; } ;
struct platform_device {TYPE_1__ dev; } ;
struct imxuart_platform_data {int /*<<< orphan*/  (* exit ) (struct platform_device*) ;} ;
struct TYPE_4__ {int /*<<< orphan*/  membase; } ;
struct imx_port {TYPE_2__ port; int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  imx_reg ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct imx_port*) ; 
 struct imx_port* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct platform_device*) ; 
 int /*<<< orphan*/  uart_remove_one_port (int /*<<< orphan*/ *,TYPE_2__*) ; 

__attribute__((used)) static int serial_imx_remove(struct platform_device *pdev)
{
	struct imxuart_platform_data *pdata;
	struct imx_port *sport = platform_get_drvdata(pdev);

	pdata = pdev->dev.platform_data;

	platform_set_drvdata(pdev, NULL);

	if (sport) {
		uart_remove_one_port(&imx_reg, &sport->port);
		clk_put(sport->clk);
	}

	clk_disable(sport->clk);

	if (pdata->exit)
		pdata->exit(pdev);

	iounmap(sport->port.membase);
	kfree(sport);

	return 0;
}