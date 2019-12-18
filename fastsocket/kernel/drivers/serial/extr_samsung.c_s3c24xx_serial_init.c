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
struct s3c24xx_uart_info {int dummy; } ;
struct platform_driver {int /*<<< orphan*/  resume; int /*<<< orphan*/  suspend; } ;

/* Variables and functions */
 int /*<<< orphan*/  dbg (char*,struct platform_driver*,struct s3c24xx_uart_info*) ; 
 int platform_driver_register (struct platform_driver*) ; 
 int /*<<< orphan*/  s3c24xx_serial_resume ; 
 int /*<<< orphan*/  s3c24xx_serial_suspend ; 

int s3c24xx_serial_init(struct platform_driver *drv,
			struct s3c24xx_uart_info *info)
{
	dbg("s3c24xx_serial_init(%p,%p)\n", drv, info);

#ifdef CONFIG_PM
	drv->suspend = s3c24xx_serial_suspend;
	drv->resume = s3c24xx_serial_resume;
#endif

	return platform_driver_register(drv);
}