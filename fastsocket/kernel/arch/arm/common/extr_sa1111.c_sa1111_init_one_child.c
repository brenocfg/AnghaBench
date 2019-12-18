#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct sa1111_dev_info {int /*<<< orphan*/  irq; int /*<<< orphan*/  skpcr_mask; scalar_t__ offset; int /*<<< orphan*/  devid; } ;
struct TYPE_12__ {int* dma_mask; int /*<<< orphan*/  coherent_dma_mask; int /*<<< orphan*/  release; int /*<<< orphan*/ * bus; TYPE_1__* parent; } ;
struct TYPE_11__ {int /*<<< orphan*/  name; int /*<<< orphan*/  flags; scalar_t__ start; scalar_t__ end; } ;
struct sa1111_dev {int dma_mask; TYPE_4__ dev; TYPE_2__ res; int /*<<< orphan*/  irq; int /*<<< orphan*/  skpcr_mask; scalar_t__ mapbase; int /*<<< orphan*/  devid; } ;
struct sa1111 {TYPE_1__* dev; scalar_t__ base; scalar_t__ phys; } ;
struct resource {int dummy; } ;
struct TYPE_10__ {int* dma_mask; int /*<<< orphan*/  coherent_dma_mask; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  dev_err (TYPE_4__*,char*) ; 
 int /*<<< orphan*/  dev_name (TYPE_4__*) ; 
 int /*<<< orphan*/  dev_set_name (TYPE_4__*,char*,...) ; 
 int device_register (TYPE_4__*) ; 
 int /*<<< orphan*/  device_unregister (TYPE_4__*) ; 
 int dmabounce_register_dev (TYPE_4__*,int,int) ; 
 int /*<<< orphan*/  kfree (struct sa1111_dev*) ; 
 struct sa1111_dev* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_resource (TYPE_2__*) ; 
 int request_resource (struct resource*,TYPE_2__*) ; 
 int /*<<< orphan*/  sa1111_bus_type ; 
 int /*<<< orphan*/  sa1111_dev_release ; 

__attribute__((used)) static int
sa1111_init_one_child(struct sa1111 *sachip, struct resource *parent,
		      struct sa1111_dev_info *info)
{
	struct sa1111_dev *dev;
	int ret;

	dev = kzalloc(sizeof(struct sa1111_dev), GFP_KERNEL);
	if (!dev) {
		ret = -ENOMEM;
		goto out;
	}

	dev_set_name(&dev->dev, "%4.4lx", info->offset);
	dev->devid	 = info->devid;
	dev->dev.parent  = sachip->dev;
	dev->dev.bus     = &sa1111_bus_type;
	dev->dev.release = sa1111_dev_release;
	dev->dev.coherent_dma_mask = sachip->dev->coherent_dma_mask;
	dev->res.start   = sachip->phys + info->offset;
	dev->res.end     = dev->res.start + 511;
	dev->res.name    = dev_name(&dev->dev);
	dev->res.flags   = IORESOURCE_MEM;
	dev->mapbase     = sachip->base + info->offset;
	dev->skpcr_mask  = info->skpcr_mask;
	memmove(dev->irq, info->irq, sizeof(dev->irq));

	ret = request_resource(parent, &dev->res);
	if (ret) {
		printk("SA1111: failed to allocate resource for %s\n",
			dev->res.name);
		dev_set_name(&dev->dev, NULL);
		kfree(dev);
		goto out;
	}


	ret = device_register(&dev->dev);
	if (ret) {
		release_resource(&dev->res);
		kfree(dev);
		goto out;
	}

#ifdef CONFIG_DMABOUNCE
	/*
	 * If the parent device has a DMA mask associated with it,
	 * propagate it down to the children.
	 */
	if (sachip->dev->dma_mask) {
		dev->dma_mask = *sachip->dev->dma_mask;
		dev->dev.dma_mask = &dev->dma_mask;

		if (dev->dma_mask != 0xffffffffUL) {
			ret = dmabounce_register_dev(&dev->dev, 1024, 4096);
			if (ret) {
				dev_err(&dev->dev, "SA1111: Failed to register"
					" with dmabounce\n");
				device_unregister(&dev->dev);
			}
		}
	}
#endif

out:
	return ret;
}