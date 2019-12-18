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
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct platform_device {TYPE_1__ dev; } ;
struct pcf50633_subdev_pdata {struct pcf50633* pcf; } ;
struct pcf50633 {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 struct pcf50633_subdev_pdata* kmalloc (int,int /*<<< orphan*/ ) ; 
 int platform_device_add (struct platform_device*) ; 
 int /*<<< orphan*/  platform_device_add_data (struct platform_device*,struct pcf50633_subdev_pdata*,int) ; 
 struct platform_device* platform_device_alloc (char const*,int) ; 
 int /*<<< orphan*/  platform_device_put (struct platform_device*) ; 

__attribute__((used)) static void
pcf50633_client_dev_register(struct pcf50633 *pcf, const char *name,
						struct platform_device **pdev)
{
	struct pcf50633_subdev_pdata *subdev_pdata;
	int ret;

	*pdev = platform_device_alloc(name, -1);
	if (!*pdev) {
		dev_err(pcf->dev, "Falied to allocate %s\n", name);
		return;
	}

	subdev_pdata = kmalloc(sizeof(*subdev_pdata), GFP_KERNEL);
	if (!subdev_pdata) {
		dev_err(pcf->dev, "Error allocating subdev pdata\n");
		platform_device_put(*pdev);
	}

	subdev_pdata->pcf = pcf;
	platform_device_add_data(*pdev, subdev_pdata, sizeof(*subdev_pdata));

	(*pdev)->dev.parent = pcf->dev;

	ret = platform_device_add(*pdev);
	if (ret) {
		dev_err(pcf->dev, "Failed to register %s: %d\n", name, ret);
		platform_device_put(*pdev);
		*pdev = NULL;
	}
}