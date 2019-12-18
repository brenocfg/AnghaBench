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
struct resource {int start; } ;
struct pnp_dev {int active; int /*<<< orphan*/  number; int /*<<< orphan*/  dev; TYPE_1__* card; } ;
struct TYPE_2__ {int /*<<< orphan*/  number; } ;

/* Variables and functions */
 int /*<<< orphan*/  IORESOURCE_DMA ; 
 int /*<<< orphan*/  IORESOURCE_IO ; 
 int /*<<< orphan*/  IORESOURCE_IRQ ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ ISAPNP_CFG_DMA ; 
 scalar_t__ ISAPNP_CFG_IRQ ; 
 scalar_t__ ISAPNP_CFG_MEM ; 
 scalar_t__ ISAPNP_CFG_PORT ; 
 int ISAPNP_MAX_DMA ; 
 int ISAPNP_MAX_IRQ ; 
 int ISAPNP_MAX_MEM ; 
 int ISAPNP_MAX_PORT ; 
 int /*<<< orphan*/  isapnp_activate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isapnp_cfg_begin (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isapnp_cfg_end () ; 
 int /*<<< orphan*/  isapnp_write_byte (scalar_t__,int) ; 
 int /*<<< orphan*/  isapnp_write_word (scalar_t__,int) ; 
 int /*<<< orphan*/  pnp_dbg (int /*<<< orphan*/ *,char*,...) ; 
 struct resource* pnp_get_resource (struct pnp_dev*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ pnp_resource_enabled (struct resource*) ; 

__attribute__((used)) static int isapnp_set_resources(struct pnp_dev *dev)
{
	struct resource *res;
	int tmp;

	pnp_dbg(&dev->dev, "set resources\n");
	isapnp_cfg_begin(dev->card->number, dev->number);
	dev->active = 1;
	for (tmp = 0; tmp < ISAPNP_MAX_PORT; tmp++) {
		res = pnp_get_resource(dev, IORESOURCE_IO, tmp);
		if (pnp_resource_enabled(res)) {
			pnp_dbg(&dev->dev, "  set io  %d to %#llx\n",
				tmp, (unsigned long long) res->start);
			isapnp_write_word(ISAPNP_CFG_PORT + (tmp << 1),
					  res->start);
		}
	}
	for (tmp = 0; tmp < ISAPNP_MAX_IRQ; tmp++) {
		res = pnp_get_resource(dev, IORESOURCE_IRQ, tmp);
		if (pnp_resource_enabled(res)) {
			int irq = res->start;
			if (irq == 2)
				irq = 9;
			pnp_dbg(&dev->dev, "  set irq %d to %d\n", tmp, irq);
			isapnp_write_byte(ISAPNP_CFG_IRQ + (tmp << 1), irq);
		}
	}
	for (tmp = 0; tmp < ISAPNP_MAX_DMA; tmp++) {
		res = pnp_get_resource(dev, IORESOURCE_DMA, tmp);
		if (pnp_resource_enabled(res)) {
			pnp_dbg(&dev->dev, "  set dma %d to %lld\n",
				tmp, (unsigned long long) res->start);
			isapnp_write_byte(ISAPNP_CFG_DMA + tmp, res->start);
		}
	}
	for (tmp = 0; tmp < ISAPNP_MAX_MEM; tmp++) {
		res = pnp_get_resource(dev, IORESOURCE_MEM, tmp);
		if (pnp_resource_enabled(res)) {
			pnp_dbg(&dev->dev, "  set mem %d to %#llx\n",
				tmp, (unsigned long long) res->start);
			isapnp_write_word(ISAPNP_CFG_MEM + (tmp << 3),
					  (res->start >> 8) & 0xffff);
		}
	}
	/* FIXME: We aren't handling 32bit mems properly here */
	isapnp_activate(dev->number);
	isapnp_cfg_end();
	return 0;
}