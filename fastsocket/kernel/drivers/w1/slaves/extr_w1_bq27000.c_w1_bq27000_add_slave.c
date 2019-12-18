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
struct w1_slave {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/ * parent; } ;
struct platform_device {TYPE_1__ dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ *,struct platform_device*) ; 
 int platform_device_add (struct platform_device*) ; 
 struct platform_device* platform_device_alloc (char*,int) ; 
 int /*<<< orphan*/  platform_device_unregister (struct platform_device*) ; 

__attribute__((used)) static int w1_bq27000_add_slave(struct w1_slave *sl)
{
	int ret;
	int id = 1;
	struct platform_device *pdev;

	pdev = platform_device_alloc("bq27000-battery", id);
	if (!pdev) {
		ret = -ENOMEM;
		return ret;
	}
	pdev->dev.parent = &sl->dev;

	ret = platform_device_add(pdev);
	if (ret)
		goto pdev_add_failed;

	dev_set_drvdata(&sl->dev, pdev);

	goto success;

pdev_add_failed:
	platform_device_unregister(pdev);
success:
	return ret;
}