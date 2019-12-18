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
struct pnp_protocol {int /*<<< orphan*/  number; int /*<<< orphan*/  dev; } ;
struct pnp_id {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * release; int /*<<< orphan*/  coherent_dma_mask; int /*<<< orphan*/ * dma_mask; int /*<<< orphan*/ * bus; int /*<<< orphan*/ * parent; } ;
struct pnp_dev {int number; struct pnp_protocol* protocol; TYPE_1__ dev; int /*<<< orphan*/  dma_mask; int /*<<< orphan*/  options; int /*<<< orphan*/  resources; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_set_name (TYPE_1__*,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  kfree (struct pnp_dev*) ; 
 struct pnp_dev* kzalloc (int,int /*<<< orphan*/ ) ; 
 struct pnp_id* pnp_add_id (struct pnp_dev*,char*) ; 
 int /*<<< orphan*/  pnp_bus_type ; 
 int /*<<< orphan*/  pnp_release_device ; 

struct pnp_dev *pnp_alloc_dev(struct pnp_protocol *protocol, int id, char *pnpid)
{
	struct pnp_dev *dev;
	struct pnp_id *dev_id;

	dev = kzalloc(sizeof(struct pnp_dev), GFP_KERNEL);
	if (!dev)
		return NULL;

	INIT_LIST_HEAD(&dev->resources);
	INIT_LIST_HEAD(&dev->options);
	dev->protocol = protocol;
	dev->number = id;
	dev->dma_mask = DMA_BIT_MASK(24);

	dev->dev.parent = &dev->protocol->dev;
	dev->dev.bus = &pnp_bus_type;
	dev->dev.dma_mask = &dev->dma_mask;
	dev->dev.coherent_dma_mask = dev->dma_mask;
	dev->dev.release = &pnp_release_device;

	dev_set_name(&dev->dev, "%02x:%02x", dev->protocol->number, dev->number);

	dev_id = pnp_add_id(dev, pnpid);
	if (!dev_id) {
		kfree(dev);
		return NULL;
	}

	return dev;
}