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
struct resource {int /*<<< orphan*/  start; } ;
struct platform_device {int dummy; } ;
struct mpsc_port_info {int /*<<< orphan*/ * sdma_base; int /*<<< orphan*/ * mpsc_base; int /*<<< orphan*/  brg_base_p; void* brg_base; int /*<<< orphan*/  sdma_base_p; int /*<<< orphan*/  mpsc_base_p; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  MPSC_BASE_ORDER ; 
 int /*<<< orphan*/  MPSC_BRG_BASE_ORDER ; 
 int /*<<< orphan*/  MPSC_BRG_REG_BLOCK_SIZE ; 
 int /*<<< orphan*/  MPSC_REG_BLOCK_SIZE ; 
 int /*<<< orphan*/  MPSC_SDMA_BASE_ORDER ; 
 int /*<<< orphan*/  MPSC_SDMA_REG_BLOCK_SIZE ; 
 void* ioremap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mpsc_resource_err (char*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ request_mem_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int mpsc_drv_map_regs(struct mpsc_port_info *pi,
		struct platform_device *pd)
{
	struct resource	*r;

	if ((r = platform_get_resource(pd, IORESOURCE_MEM, MPSC_BASE_ORDER))
			&& request_mem_region(r->start, MPSC_REG_BLOCK_SIZE,
			"mpsc_regs")) {
		pi->mpsc_base = ioremap(r->start, MPSC_REG_BLOCK_SIZE);
		pi->mpsc_base_p = r->start;
	} else {
		mpsc_resource_err("MPSC base");
		goto err;
	}

	if ((r = platform_get_resource(pd, IORESOURCE_MEM,
					MPSC_SDMA_BASE_ORDER))
			&& request_mem_region(r->start,
				MPSC_SDMA_REG_BLOCK_SIZE, "sdma_regs")) {
		pi->sdma_base = ioremap(r->start,MPSC_SDMA_REG_BLOCK_SIZE);
		pi->sdma_base_p = r->start;
	} else {
		mpsc_resource_err("SDMA base");
		if (pi->mpsc_base) {
			iounmap(pi->mpsc_base);
			pi->mpsc_base = NULL;
		}
		goto err;
	}

	if ((r = platform_get_resource(pd,IORESOURCE_MEM,MPSC_BRG_BASE_ORDER))
			&& request_mem_region(r->start,
				MPSC_BRG_REG_BLOCK_SIZE, "brg_regs")) {
		pi->brg_base = ioremap(r->start, MPSC_BRG_REG_BLOCK_SIZE);
		pi->brg_base_p = r->start;
	} else {
		mpsc_resource_err("BRG base");
		if (pi->mpsc_base) {
			iounmap(pi->mpsc_base);
			pi->mpsc_base = NULL;
		}
		if (pi->sdma_base) {
			iounmap(pi->sdma_base);
			pi->sdma_base = NULL;
		}
		goto err;
	}
	return 0;

err:
	return -ENOMEM;
}