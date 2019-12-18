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
struct resource {int /*<<< orphan*/  start; } ;
struct platform_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  mpsc_routing_base_p; void* mpsc_routing_base; int /*<<< orphan*/  sdma_intr_base_p; void* sdma_intr_base; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  MPSC_ROUTING_BASE_ORDER ; 
 int /*<<< orphan*/  MPSC_ROUTING_REG_BLOCK_SIZE ; 
 int /*<<< orphan*/  MPSC_SDMA_INTR_BASE_ORDER ; 
 int /*<<< orphan*/  MPSC_SDMA_INTR_REG_BLOCK_SIZE ; 
 void* ioremap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iounmap (void*) ; 
 int /*<<< orphan*/  mpsc_resource_err (char*) ; 
 TYPE_1__ mpsc_shared_regs ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_mem_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ request_mem_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int mpsc_shared_map_regs(struct platform_device *pd)
{
	struct resource	*r;

	if ((r = platform_get_resource(pd, IORESOURCE_MEM,
					MPSC_ROUTING_BASE_ORDER))
			&& request_mem_region(r->start,
				MPSC_ROUTING_REG_BLOCK_SIZE,
				"mpsc_routing_regs")) {
		mpsc_shared_regs.mpsc_routing_base = ioremap(r->start,
				MPSC_ROUTING_REG_BLOCK_SIZE);
		mpsc_shared_regs.mpsc_routing_base_p = r->start;
	} else {
		mpsc_resource_err("MPSC routing base");
		return -ENOMEM;
	}

	if ((r = platform_get_resource(pd, IORESOURCE_MEM,
					MPSC_SDMA_INTR_BASE_ORDER))
			&& request_mem_region(r->start,
				MPSC_SDMA_INTR_REG_BLOCK_SIZE,
				"sdma_intr_regs")) {
		mpsc_shared_regs.sdma_intr_base = ioremap(r->start,
			MPSC_SDMA_INTR_REG_BLOCK_SIZE);
		mpsc_shared_regs.sdma_intr_base_p = r->start;
	} else {
		iounmap(mpsc_shared_regs.mpsc_routing_base);
		release_mem_region(mpsc_shared_regs.mpsc_routing_base_p,
				MPSC_ROUTING_REG_BLOCK_SIZE);
		mpsc_resource_err("SDMA intr base");
		return -ENOMEM;
	}

	return 0;
}