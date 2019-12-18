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
struct TYPE_2__ {int /*<<< orphan*/  start; } ;
struct lm_device {TYPE_1__ resource; int /*<<< orphan*/  dev; } ;
struct impd1_module {int /*<<< orphan*/  base; int /*<<< orphan*/ * clks; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SZ_4K ; 
 int /*<<< orphan*/  clkdev_drop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_for_each_child (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  impd1_remove_one ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct impd1_module*) ; 
 struct impd1_module* lm_get_drvdata (struct lm_device*) ; 
 int /*<<< orphan*/  lm_set_drvdata (struct lm_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_mem_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void impd1_remove(struct lm_device *dev)
{
	struct impd1_module *impd1 = lm_get_drvdata(dev);
	int i;

	device_for_each_child(&dev->dev, NULL, impd1_remove_one);

	for (i = 0; i < ARRAY_SIZE(impd1->clks); i++)
		clkdev_drop(impd1->clks[i]);

	lm_set_drvdata(dev, NULL);

	iounmap(impd1->base);
	kfree(impd1);
	release_mem_region(dev->resource.start, SZ_4K);
}