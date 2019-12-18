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
typedef  unsigned long u_long ;
struct socket_data {int /*<<< orphan*/  mem_db; } ;
struct resource {int dummy; } ;
struct pcmcia_socket {int features; TYPE_1__* cb_dev; struct socket_data* resource_data; int /*<<< orphan*/  dev; } ;
struct pcmcia_align_data {unsigned long mask; unsigned long offset; int /*<<< orphan*/ * map; } ;
struct TYPE_2__ {int /*<<< orphan*/  bus; } ;

/* Variables and functions */
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int SS_CAP_PAGE_REGS ; 
 int allocate_resource (int /*<<< orphan*/ *,struct resource*,unsigned long,unsigned long,unsigned long,int,int /*<<< orphan*/ ,struct pcmcia_align_data*) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iomem_resource ; 
 int /*<<< orphan*/  kfree (struct resource*) ; 
 struct resource* make_resource (int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int pci_bus_alloc_resource (int /*<<< orphan*/ ,struct resource*,unsigned long,int,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct pcmcia_align_data*) ; 
 int /*<<< orphan*/  pcmcia_align ; 
 int /*<<< orphan*/  rsrc_mutex ; 

__attribute__((used)) static struct resource * nonstatic_find_mem_region(u_long base, u_long num,
		u_long align, int low, struct pcmcia_socket *s)
{
	struct resource *res = make_resource(0, num, IORESOURCE_MEM, dev_name(&s->dev));
	struct socket_data *s_data = s->resource_data;
	struct pcmcia_align_data data;
	unsigned long min, max;
	int ret, i;

	low = low || !(s->features & SS_CAP_PAGE_REGS);

	data.mask = align - 1;
	data.offset = base & data.mask;
	data.map = &s_data->mem_db;

	for (i = 0; i < 2; i++) {
		if (low) {
			max = 0x100000UL;
			min = base < max ? base : 0;
		} else {
			max = ~0UL;
			min = 0x100000UL + base;
		}

		mutex_lock(&rsrc_mutex);
#ifdef CONFIG_PCI
		if (s->cb_dev) {
			ret = pci_bus_alloc_resource(s->cb_dev->bus, res, num,
						     1, min, 0,
						     pcmcia_align, &data);
		} else
#endif
			ret = allocate_resource(&iomem_resource, res, num, min,
						max, 1, pcmcia_align, &data);
		mutex_unlock(&rsrc_mutex);
		if (ret == 0 || low)
			break;
		low = 1;
	}

	if (ret != 0) {
		kfree(res);
		res = NULL;
	}
	return res;
}