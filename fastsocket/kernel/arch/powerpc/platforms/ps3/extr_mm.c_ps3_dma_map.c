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
typedef  int /*<<< orphan*/  u64 ;
struct ps3_dma_region {TYPE_1__* region_ops; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_2__ {int (* map ) (struct ps3_dma_region*,unsigned long,unsigned long,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int stub1 (struct ps3_dma_region*,unsigned long,unsigned long,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int ps3_dma_map(struct ps3_dma_region *r, unsigned long virt_addr,
	unsigned long len, dma_addr_t *bus_addr,
	u64 iopte_flag)
{
	return r->region_ops->map(r, virt_addr, len, bus_addr, iopte_flag);
}