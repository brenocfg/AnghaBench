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

/* Variables and functions */
 int /*<<< orphan*/  pm_cpu_prep ; 
 int /*<<< orphan*/  pm_cpu_sleep ; 
 int pm_uart_udivslot ; 
 int /*<<< orphan*/  s3c64xx_cpu_suspend ; 
 int /*<<< orphan*/  s3c64xx_pm_prepare ; 

__attribute__((used)) static int s3c64xx_pm_init(void)
{
	pm_cpu_prep = s3c64xx_pm_prepare;
	pm_cpu_sleep = s3c64xx_cpu_suspend;
	pm_uart_udivslot = 1;
	return 0;
}