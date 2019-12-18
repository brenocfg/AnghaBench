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
struct TYPE_2__ {int /*<<< orphan*/ * parent; } ;
struct i2c_adapter {int retries; int nr; int /*<<< orphan*/  name; TYPE_1__ dev; int /*<<< orphan*/ * algo; int /*<<< orphan*/  owner; } ;
struct sh_mobile_i2c_data {int /*<<< orphan*/  clk; int /*<<< orphan*/ * reg; int /*<<< orphan*/  wait; int /*<<< orphan*/  lock; struct i2c_adapter adap; int /*<<< orphan*/ * dev; } ;
struct resource {int /*<<< orphan*/  start; } ;
struct platform_device {int id; int /*<<< orphan*/  dev; int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  clk_name ;

/* Variables and functions */
 int ENOENT ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  clk_get (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  clk_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int i2c_add_numbered_adapter (struct i2c_adapter*) ; 
 int /*<<< orphan*/  i2c_set_adapdata (struct i2c_adapter*,struct sh_mobile_i2c_data*) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ioremap (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct sh_mobile_i2c_data*) ; 
 struct sh_mobile_i2c_data* kzalloc (int,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct sh_mobile_i2c_data*) ; 
 int /*<<< orphan*/  pm_runtime_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_suspend_ignore_children (int /*<<< orphan*/ *,int) ; 
 int resource_size (struct resource*) ; 
 int /*<<< orphan*/  sh_mobile_i2c_algorithm ; 
 int sh_mobile_i2c_hook_irqs (struct platform_device*,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int sh_mobile_i2c_probe(struct platform_device *dev)
{
	struct sh_mobile_i2c_data *pd;
	struct i2c_adapter *adap;
	struct resource *res;
	char clk_name[8];
	int size;
	int ret;

	pd = kzalloc(sizeof(struct sh_mobile_i2c_data), GFP_KERNEL);
	if (pd == NULL) {
		dev_err(&dev->dev, "cannot allocate private data\n");
		return -ENOMEM;
	}

	snprintf(clk_name, sizeof(clk_name), "i2c%d", dev->id);
	pd->clk = clk_get(&dev->dev, clk_name);
	if (IS_ERR(pd->clk)) {
		dev_err(&dev->dev, "cannot get clock \"%s\"\n", clk_name);
		ret = PTR_ERR(pd->clk);
		goto err;
	}

	ret = sh_mobile_i2c_hook_irqs(dev, 1);
	if (ret) {
		dev_err(&dev->dev, "cannot request IRQ\n");
		goto err_clk;
	}

	pd->dev = &dev->dev;
	platform_set_drvdata(dev, pd);

	res = platform_get_resource(dev, IORESOURCE_MEM, 0);
	if (res == NULL) {
		dev_err(&dev->dev, "cannot find IO resource\n");
		ret = -ENOENT;
		goto err_irq;
	}

	size = resource_size(res);

	pd->reg = ioremap(res->start, size);
	if (pd->reg == NULL) {
		dev_err(&dev->dev, "cannot map IO\n");
		ret = -ENXIO;
		goto err_irq;
	}

	/* Enable Runtime PM for this device.
	 *
	 * Also tell the Runtime PM core to ignore children
	 * for this device since it is valid for us to suspend
	 * this I2C master driver even though the slave devices
	 * on the I2C bus may not be suspended.
	 *
	 * The state of the I2C hardware bus is unaffected by
	 * the Runtime PM state.
	 */
	pm_suspend_ignore_children(&dev->dev, true);
	pm_runtime_enable(&dev->dev);

	/* setup the private data */
	adap = &pd->adap;
	i2c_set_adapdata(adap, pd);

	adap->owner = THIS_MODULE;
	adap->algo = &sh_mobile_i2c_algorithm;
	adap->dev.parent = &dev->dev;
	adap->retries = 5;
	adap->nr = dev->id;

	strlcpy(adap->name, dev->name, sizeof(adap->name));

	spin_lock_init(&pd->lock);
	init_waitqueue_head(&pd->wait);

	ret = i2c_add_numbered_adapter(adap);
	if (ret < 0) {
		dev_err(&dev->dev, "cannot add numbered adapter\n");
		goto err_all;
	}

	return 0;

 err_all:
	iounmap(pd->reg);
 err_irq:
	sh_mobile_i2c_hook_irqs(dev, 0);
 err_clk:
	clk_put(pd->clk);
 err:
	kfree(pd);
	return ret;
}