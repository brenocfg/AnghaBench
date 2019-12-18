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
struct resource {int start; int flags; int end; } ;
struct pnp_dma {int flags; int map; } ;
struct pnp_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int IORESOURCE_AUTO ; 
 int IORESOURCE_DISABLED ; 
 int /*<<< orphan*/  IORESOURCE_DMA ; 
 unsigned short MAX_DMA_CHANNELS ; 
 int /*<<< orphan*/  pnp_add_dma_resource (struct pnp_dev*,unsigned short,int) ; 
 scalar_t__ pnp_check_dma (struct pnp_dev*,struct resource*) ; 
 int /*<<< orphan*/  pnp_dbg (int /*<<< orphan*/ *,char*,int,...) ; 
 struct resource* pnp_get_resource (struct pnp_dev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int pnp_assign_dma(struct pnp_dev *dev, struct pnp_dma *rule, int idx)
{
	struct resource *res, local_res;
	int i;

	/* DMA priority: this table is good for i386 */
	static unsigned short xtab[8] = {
		1, 3, 5, 6, 7, 0, 2, 4
	};

	res = pnp_get_resource(dev, IORESOURCE_DMA, idx);
	if (res) {
		pnp_dbg(&dev->dev, "  dma %d already set to %d flags %#lx\n",
			idx, (int) res->start, res->flags);
		return 0;
	}

	res = &local_res;
	res->flags = rule->flags | IORESOURCE_AUTO;
	res->start = -1;
	res->end = -1;

	for (i = 0; i < 8; i++) {
		if (rule->map & (1 << xtab[i])) {
			res->start = res->end = xtab[i];
			if (pnp_check_dma(dev, res))
				goto __add;
		}
	}
#ifdef MAX_DMA_CHANNELS
	res->start = res->end = MAX_DMA_CHANNELS;
#endif
	res->flags |= IORESOURCE_DISABLED;
	pnp_dbg(&dev->dev, "  disable dma %d\n", idx);

__add:
	pnp_add_dma_resource(dev, res->start, res->flags);
	return 0;
}