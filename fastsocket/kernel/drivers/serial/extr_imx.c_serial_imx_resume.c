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
struct imx_port {int /*<<< orphan*/  port; } ;

/* Variables and functions */
 int /*<<< orphan*/  imx_reg ; 
 struct imx_port* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  uart_resume_port (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int serial_imx_resume(struct platform_device *dev)
{
	struct imx_port *sport = platform_get_drvdata(dev);

	if (sport)
		uart_resume_port(&imx_reg, &sport->port);

	return 0;
}