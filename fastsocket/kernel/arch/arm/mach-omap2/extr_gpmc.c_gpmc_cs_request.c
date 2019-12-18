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
struct resource {unsigned long start; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENODEV ; 
 int ENOMEM ; 
 int GPMC_CS_NUM ; 
 int GPMC_SECTION_SHIFT ; 
 int adjust_resource (struct resource*,unsigned long,unsigned long) ; 
 int allocate_resource (int /*<<< orphan*/ *,struct resource*,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gpmc_cs_enable_mem (int,unsigned long,int /*<<< orphan*/ ) ; 
 struct resource* gpmc_cs_mem ; 
 scalar_t__ gpmc_cs_mem_enabled (int) ; 
 scalar_t__ gpmc_cs_reserved (int) ; 
 int /*<<< orphan*/  gpmc_cs_set_reserved (int,int) ; 
 unsigned long gpmc_mem_align (unsigned long) ; 
 int /*<<< orphan*/  gpmc_mem_lock ; 
 int /*<<< orphan*/  gpmc_mem_root ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int gpmc_cs_request(int cs, unsigned long size, unsigned long *base)
{
	struct resource *res = &gpmc_cs_mem[cs];
	int r = -1;

	if (cs > GPMC_CS_NUM)
		return -ENODEV;

	size = gpmc_mem_align(size);
	if (size > (1 << GPMC_SECTION_SHIFT))
		return -ENOMEM;

	spin_lock(&gpmc_mem_lock);
	if (gpmc_cs_reserved(cs)) {
		r = -EBUSY;
		goto out;
	}
	if (gpmc_cs_mem_enabled(cs))
		r = adjust_resource(res, res->start & ~(size - 1), size);
	if (r < 0)
		r = allocate_resource(&gpmc_mem_root, res, size, 0, ~0,
				      size, NULL, NULL);
	if (r < 0)
		goto out;

	gpmc_cs_enable_mem(cs, res->start, resource_size(res));
	*base = res->start;
	gpmc_cs_set_reserved(cs, 1);
out:
	spin_unlock(&gpmc_mem_lock);
	return r;
}