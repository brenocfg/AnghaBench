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
struct sh_mobile_i2c_data {int /*<<< orphan*/  clk; int /*<<< orphan*/  reg; int /*<<< orphan*/  adap; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_del_adapter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct sh_mobile_i2c_data*) ; 
 struct sh_mobile_i2c_data* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sh_mobile_i2c_hook_irqs (struct platform_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sh_mobile_i2c_remove(struct platform_device *dev)
{
	struct sh_mobile_i2c_data *pd = platform_get_drvdata(dev);

	i2c_del_adapter(&pd->adap);
	iounmap(pd->reg);
	sh_mobile_i2c_hook_irqs(dev, 0);
	clk_put(pd->clk);
	pm_runtime_disable(&dev->dev);
	kfree(pd);
	return 0;
}