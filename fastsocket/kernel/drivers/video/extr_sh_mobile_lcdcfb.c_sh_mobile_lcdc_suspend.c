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
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  sh_mobile_lcdc_stop (int /*<<< orphan*/ ) ; 
 struct platform_device* to_platform_device (struct device*) ; 

__attribute__((used)) static int sh_mobile_lcdc_suspend(struct device *dev)
{
	struct platform_device *pdev = to_platform_device(dev);

	sh_mobile_lcdc_stop(platform_get_drvdata(pdev));
	return 0;
}