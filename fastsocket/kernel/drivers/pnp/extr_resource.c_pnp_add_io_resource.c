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
struct resource {int flags; void* end; void* start; } ;
struct pnp_resource {struct resource res; } ;
struct pnp_dev {int /*<<< orphan*/  dev; } ;
typedef  void* resource_size_t ;

/* Variables and functions */
 int IORESOURCE_IO ; 
 int /*<<< orphan*/  KERN_DEBUG ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,unsigned long long,unsigned long long) ; 
 int /*<<< orphan*/  dev_printk (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,struct resource*) ; 
 struct pnp_resource* pnp_new_resource (struct pnp_dev*) ; 

struct pnp_resource *pnp_add_io_resource(struct pnp_dev *dev,
					 resource_size_t start,
					 resource_size_t end, int flags)
{
	struct pnp_resource *pnp_res;
	struct resource *res;

	pnp_res = pnp_new_resource(dev);
	if (!pnp_res) {
		dev_err(&dev->dev, "can't add resource for IO %#llx-%#llx\n",
			(unsigned long long) start,
			(unsigned long long) end);
		return NULL;
	}

	res = &pnp_res->res;
	res->flags = IORESOURCE_IO | flags;
	res->start = start;
	res->end = end;

	dev_printk(KERN_DEBUG, &dev->dev, "%pR\n", res);
	return pnp_res;
}