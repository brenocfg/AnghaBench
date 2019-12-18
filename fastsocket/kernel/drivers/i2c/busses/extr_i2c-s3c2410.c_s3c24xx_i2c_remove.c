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
struct s3c24xx_i2c {struct s3c24xx_i2c* ioarea; int /*<<< orphan*/  regs; int /*<<< orphan*/  clk; int /*<<< orphan*/  irq; int /*<<< orphan*/  adap; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct s3c24xx_i2c*) ; 
 int /*<<< orphan*/  i2c_del_adapter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct s3c24xx_i2c*) ; 
 struct s3c24xx_i2c* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  release_resource (struct s3c24xx_i2c*) ; 
 int /*<<< orphan*/  s3c24xx_i2c_deregister_cpufreq (struct s3c24xx_i2c*) ; 

__attribute__((used)) static int s3c24xx_i2c_remove(struct platform_device *pdev)
{
	struct s3c24xx_i2c *i2c = platform_get_drvdata(pdev);

	s3c24xx_i2c_deregister_cpufreq(i2c);

	i2c_del_adapter(&i2c->adap);
	free_irq(i2c->irq, i2c);

	clk_disable(i2c->clk);
	clk_put(i2c->clk);

	iounmap(i2c->regs);

	release_resource(i2c->ioarea);
	kfree(i2c->ioarea);
	kfree(i2c);

	return 0;
}