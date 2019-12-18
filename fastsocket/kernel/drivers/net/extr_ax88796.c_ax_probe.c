#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct resource {int start; int flags; int end; } ;
struct TYPE_6__ {TYPE_1__* platform_data; } ;
struct platform_device {TYPE_3__ dev; int /*<<< orphan*/  name; } ;
struct net_device {int irq; unsigned long base_addr; } ;
struct ax_device {int irqflags; int* reg_offsets; int /*<<< orphan*/ * mem; int /*<<< orphan*/ * mem2; int /*<<< orphan*/ * map2; TYPE_1__* plat; struct platform_device* dev; int /*<<< orphan*/  mii_lock; } ;
struct TYPE_5__ {int* reg_offset; int /*<<< orphan*/ * mem; int /*<<< orphan*/  rxcr_base; } ;
struct TYPE_4__ {int* reg_offsets; int /*<<< orphan*/  rcr_val; } ;

/* Variables and functions */
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  IORESOURCE_IRQ ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int IRQF_TRIGGER_MASK ; 
 struct net_device* ax__alloc_ei_netdev (int) ; 
 int ax_init_dev (struct net_device*,int) ; 
 int /*<<< orphan*/  dev_err (TYPE_3__*,char*,...) ; 
 TYPE_2__ ei_status ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 void* ioremap (int,size_t) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct ax_device*,int /*<<< orphan*/ ,int) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct net_device*) ; 
 int /*<<< orphan*/  release_resource (int /*<<< orphan*/ *) ; 
 void* request_mem_region (int,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 struct ax_device* to_ax_dev (struct net_device*) ; 

__attribute__((used)) static int ax_probe(struct platform_device *pdev)
{
	struct net_device *dev;
	struct ax_device  *ax;
	struct resource   *res;
	size_t size;
	int ret = 0;

	dev = ax__alloc_ei_netdev(sizeof(struct ax_device));
	if (dev == NULL)
		return -ENOMEM;

	/* ok, let's setup our device */
	ax = to_ax_dev(dev);

	memset(ax, 0, sizeof(struct ax_device));

	spin_lock_init(&ax->mii_lock);

	ax->dev = pdev;
	ax->plat = pdev->dev.platform_data;
	platform_set_drvdata(pdev, dev);

	ei_status.rxcr_base  = ax->plat->rcr_val;

	/* find the platform resources */

	res = platform_get_resource(pdev, IORESOURCE_IRQ, 0);
	if (res == NULL) {
		dev_err(&pdev->dev, "no IRQ specified\n");
		goto exit_mem;
	}

	dev->irq = res->start;
	ax->irqflags = res->flags & IRQF_TRIGGER_MASK;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (res == NULL) {
		dev_err(&pdev->dev, "no MEM specified\n");
		ret = -ENXIO;
		goto exit_mem;
	}

	size = (res->end - res->start) + 1;

	/* setup the register offsets from either the platform data
	 * or by using the size of the resource provided */

	if (ax->plat->reg_offsets)
		ei_status.reg_offset = ax->plat->reg_offsets;
	else {
		ei_status.reg_offset = ax->reg_offsets;
		for (ret = 0; ret < 0x18; ret++)
			ax->reg_offsets[ret] = (size / 0x18) * ret;
	}

	ax->mem = request_mem_region(res->start, size, pdev->name);
	if (ax->mem == NULL) {
		dev_err(&pdev->dev, "cannot reserve registers\n");
 		ret = -ENXIO;
		goto exit_mem;
	}

	ei_status.mem = ioremap(res->start, size);
	dev->base_addr = (unsigned long)ei_status.mem;

	if (ei_status.mem == NULL) {
		dev_err(&pdev->dev, "Cannot ioremap area (%08llx,%08llx)\n",
			(unsigned long long)res->start,
			(unsigned long long)res->end);

 		ret = -ENXIO;
		goto exit_req;
	}

	/* look for reset area */

	res = platform_get_resource(pdev, IORESOURCE_MEM, 1);
	if (res == NULL) {
		if (!ax->plat->reg_offsets) {
			for (ret = 0; ret < 0x20; ret++)
				ax->reg_offsets[ret] = (size / 0x20) * ret;
		}

		ax->map2 = NULL;
	} else {
 		size = (res->end - res->start) + 1;

		ax->mem2 = request_mem_region(res->start, size, pdev->name);
		if (ax->mem == NULL) {
			dev_err(&pdev->dev, "cannot reserve registers\n");
			ret = -ENXIO;
			goto exit_mem1;
		}

		ax->map2 = ioremap(res->start, size);
		if (ax->map2 == NULL) {
			dev_err(&pdev->dev, "cannot map reset register\n");
			ret = -ENXIO;
			goto exit_mem2;
		}

		ei_status.reg_offset[0x1f] = ax->map2 - ei_status.mem;
	}

	/* got resources, now initialise and register device */

	ret = ax_init_dev(dev, 1);
	if (!ret)
		return 0;

	if (ax->map2 == NULL)
		goto exit_mem1;

	iounmap(ax->map2);

 exit_mem2:
	release_resource(ax->mem2);
	kfree(ax->mem2);

 exit_mem1:
	iounmap(ei_status.mem);

 exit_req:
	release_resource(ax->mem);
	kfree(ax->mem);

 exit_mem:
	free_netdev(dev);

	return ret;
}