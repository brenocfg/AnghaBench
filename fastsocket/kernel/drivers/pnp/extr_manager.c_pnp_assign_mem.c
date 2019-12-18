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
struct resource {scalar_t__ start; scalar_t__ end; int flags; } ;
struct pnp_mem {int flags; scalar_t__ size; scalar_t__ min; scalar_t__ align; scalar_t__ max; } ;
struct pnp_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EBUSY ; 
 int IORESOURCE_AUTO ; 
 int IORESOURCE_CACHEABLE ; 
 int IORESOURCE_DISABLED ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int IORESOURCE_MEM_CACHEABLE ; 
 int IORESOURCE_MEM_RANGELENGTH ; 
 int IORESOURCE_MEM_SHADOWABLE ; 
 int IORESOURCE_MEM_WRITEABLE ; 
 int IORESOURCE_RANGELENGTH ; 
 int IORESOURCE_READONLY ; 
 int IORESOURCE_SHADOWABLE ; 
 int /*<<< orphan*/  pnp_add_mem_resource (struct pnp_dev*,scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  pnp_check_mem (struct pnp_dev*,struct resource*) ; 
 int /*<<< orphan*/  pnp_dbg (int /*<<< orphan*/ *,char*,int,...) ; 
 struct resource* pnp_get_resource (struct pnp_dev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int pnp_assign_mem(struct pnp_dev *dev, struct pnp_mem *rule, int idx)
{
	struct resource *res, local_res;

	res = pnp_get_resource(dev, IORESOURCE_MEM, idx);
	if (res) {
		pnp_dbg(&dev->dev, "  mem %d already set to %#llx-%#llx "
			"flags %#lx\n", idx, (unsigned long long) res->start,
			(unsigned long long) res->end, res->flags);
		return 0;
	}

	res = &local_res;
	res->flags = rule->flags | IORESOURCE_AUTO;
	res->start = 0;
	res->end = 0;

	if (!(rule->flags & IORESOURCE_MEM_WRITEABLE))
		res->flags |= IORESOURCE_READONLY;
	if (rule->flags & IORESOURCE_MEM_CACHEABLE)
		res->flags |= IORESOURCE_CACHEABLE;
	if (rule->flags & IORESOURCE_MEM_RANGELENGTH)
		res->flags |= IORESOURCE_RANGELENGTH;
	if (rule->flags & IORESOURCE_MEM_SHADOWABLE)
		res->flags |= IORESOURCE_SHADOWABLE;

	if (!rule->size) {
		res->flags |= IORESOURCE_DISABLED;
		pnp_dbg(&dev->dev, "  mem %d disabled\n", idx);
		goto __add;
	}

	res->start = rule->min;
	res->end = res->start + rule->size - 1;

	while (!pnp_check_mem(dev, res)) {
		res->start += rule->align;
		res->end = res->start + rule->size - 1;
		if (res->start > rule->max || !rule->align) {
			pnp_dbg(&dev->dev, "  couldn't assign mem %d "
				"(min %#llx max %#llx)\n", idx,
				(unsigned long long) rule->min,
				(unsigned long long) rule->max);
			return -EBUSY;
		}
	}

__add:
	pnp_add_mem_resource(dev, res->start, res->end, res->flags);
	return 0;
}