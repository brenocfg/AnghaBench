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
struct resource {int start; int /*<<< orphan*/  flags; } ;
struct device {struct device* parent; } ;
struct platform_device {struct device dev; } ;
struct i2c_client {struct device dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct device* ERR_PTR (int) ; 
 int /*<<< orphan*/  IORESOURCE_IRQ ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,char const*) ; 
 int /*<<< orphan*/  device_init_wakeup (struct device*,int) ; 
 int platform_device_add (struct platform_device*) ; 
 int platform_device_add_data (struct platform_device*,void*,unsigned int) ; 
 int platform_device_add_resources (struct platform_device*,struct resource*,int) ; 
 struct platform_device* platform_device_alloc (char const*,int) ; 
 int /*<<< orphan*/  platform_device_put (struct platform_device*) ; 

__attribute__((used)) static struct device *add_child(struct i2c_client *client, const char *name,
		void *pdata, unsigned pdata_len,
		bool can_wakeup, int irq)
{
	struct platform_device	*pdev;
	int			status;

	pdev = platform_device_alloc(name, -1);
	if (!pdev) {
		dev_dbg(&client->dev, "can't alloc dev\n");
		status = -ENOMEM;
		goto err;
	}

	device_init_wakeup(&pdev->dev, can_wakeup);
	pdev->dev.parent = &client->dev;

	if (pdata) {
		status = platform_device_add_data(pdev, pdata, pdata_len);
		if (status < 0) {
			dev_dbg(&pdev->dev, "can't add platform_data\n");
			goto err;
		}
	}

	if (irq) {
		struct resource r = {
			.start = irq,
			.flags = IORESOURCE_IRQ,
		};

		status = platform_device_add_resources(pdev, &r, 1);
		if (status < 0) {
			dev_dbg(&pdev->dev, "can't add irq\n");
			goto err;
		}
	}

	status = platform_device_add(pdev);

err:
	if (status < 0) {
		platform_device_put(pdev);
		dev_err(&client->dev, "can't add %s dev\n", name);
		return ERR_PTR(status);
	}
	return &pdev->dev;
}