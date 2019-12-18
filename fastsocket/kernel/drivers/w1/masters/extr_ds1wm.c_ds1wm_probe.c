#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct resource {int flags; int /*<<< orphan*/  start; } ;
struct TYPE_4__ {struct mfd_cell* platform_data; } ;
struct platform_device {TYPE_1__ dev; } ;
struct mfd_cell {struct ds1wm_driver_data* driver_data; } ;
struct ds1wm_driver_data {int /*<<< orphan*/  active_high; } ;
struct ds1wm_data {int bus_shift; int /*<<< orphan*/  map; int /*<<< orphan*/  irq; int /*<<< orphan*/  active_high; struct mfd_cell* cell; struct platform_device* pdev; } ;
struct TYPE_5__ {void* data; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_IRQ ; 
 int IORESOURCE_IRQ_HIGHEDGE ; 
 int IORESOURCE_IRQ_LOWEDGE ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  IRQF_DISABLED ; 
 int /*<<< orphan*/  IRQ_TYPE_EDGE_FALLING ; 
 int /*<<< orphan*/  IRQ_TYPE_EDGE_RISING ; 
 int /*<<< orphan*/  ds1wm_down (struct ds1wm_data*) ; 
 int /*<<< orphan*/  ds1wm_isr ; 
 TYPE_2__ ds1wm_master ; 
 int /*<<< orphan*/  ds1wm_up (struct ds1wm_data*) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct ds1wm_data*) ; 
 int /*<<< orphan*/  ioremap (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct ds1wm_data*) ; 
 struct ds1wm_data* kzalloc (int,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct ds1wm_data*) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct ds1wm_data*) ; 
 int resource_size (struct resource*) ; 
 int /*<<< orphan*/  set_irq_type (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int w1_add_master_device (TYPE_2__*) ; 

__attribute__((used)) static int ds1wm_probe(struct platform_device *pdev)
{
	struct ds1wm_data *ds1wm_data;
	struct ds1wm_driver_data *plat;
	struct resource *res;
	struct mfd_cell *cell;
	int ret;

	if (!pdev)
		return -ENODEV;

	cell = pdev->dev.platform_data;
	if (!cell)
		return -ENODEV;

	ds1wm_data = kzalloc(sizeof(*ds1wm_data), GFP_KERNEL);
	if (!ds1wm_data)
		return -ENOMEM;

	platform_set_drvdata(pdev, ds1wm_data);

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (!res) {
		ret = -ENXIO;
		goto err0;
	}
	ds1wm_data->map = ioremap(res->start, resource_size(res));
	if (!ds1wm_data->map) {
		ret = -ENOMEM;
		goto err0;
	}
	plat = cell->driver_data;

	/* calculate bus shift from mem resource */
	ds1wm_data->bus_shift = resource_size(res) >> 3;

	ds1wm_data->pdev = pdev;
	ds1wm_data->cell = cell;

	res = platform_get_resource(pdev, IORESOURCE_IRQ, 0);
	if (!res) {
		ret = -ENXIO;
		goto err1;
	}
	ds1wm_data->irq = res->start;
	ds1wm_data->active_high = plat->active_high;

	if (res->flags & IORESOURCE_IRQ_HIGHEDGE)
		set_irq_type(ds1wm_data->irq, IRQ_TYPE_EDGE_RISING);
	if (res->flags & IORESOURCE_IRQ_LOWEDGE)
		set_irq_type(ds1wm_data->irq, IRQ_TYPE_EDGE_FALLING);

	ret = request_irq(ds1wm_data->irq, ds1wm_isr, IRQF_DISABLED,
			  "ds1wm", ds1wm_data);
	if (ret)
		goto err1;

	ds1wm_up(ds1wm_data);

	ds1wm_master.data = (void *)ds1wm_data;

	ret = w1_add_master_device(&ds1wm_master);
	if (ret)
		goto err2;

	return 0;

err2:
	ds1wm_down(ds1wm_data);
	free_irq(ds1wm_data->irq, ds1wm_data);
err1:
	iounmap(ds1wm_data->map);
err0:
	kfree(ds1wm_data);

	return ret;
}