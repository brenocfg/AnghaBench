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
typedef  int /*<<< orphan*/  pm_message_t ;

/* Variables and functions */
 int set_clock_run (struct platform_device*) ; 

__attribute__((used)) static int i2c_pnx_suspend(struct platform_device *pdev, pm_message_t state)
{
	int retval = 0;
#ifdef CONFIG_PM
	retval = set_clock_run(pdev);
#endif
	return retval;
}