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
struct platform_device {int dummy; } ;
struct netx_port {int /*<<< orphan*/  port; } ;

/* Variables and functions */
 int /*<<< orphan*/  netx_reg ; 
 struct netx_port* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uart_remove_one_port (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int serial_netx_remove(struct platform_device *pdev)
{
	struct netx_port *sport = platform_get_drvdata(pdev);

	platform_set_drvdata(pdev, NULL);

	if (sport)
		uart_remove_one_port(&netx_reg, &sport->port);

	return 0;
}