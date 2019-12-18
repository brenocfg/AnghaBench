#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct agp_memory {int page_count; int /*<<< orphan*/  is_flushed; } ;
typedef  int off_t ;
typedef  int dma_addr_t ;
struct TYPE_4__ {int num_dcache_entries; scalar_t__ gtt; TYPE_1__* driver; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* write_entry ) (int,int,int) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  global_cache_flush () ; 
 TYPE_2__ intel_private ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  stub1 (int,int,int) ; 

__attribute__((used)) static int i810_insert_dcache_entries(struct agp_memory *mem, off_t pg_start,
				      int type)
{
	int i;

	if ((pg_start + mem->page_count)
			> intel_private.num_dcache_entries)
		return -EINVAL;

	if (!mem->is_flushed)
		global_cache_flush();

	for (i = pg_start; i < (pg_start + mem->page_count); i++) {
		dma_addr_t addr = i << PAGE_SHIFT;
		intel_private.driver->write_entry(addr,
						  i, type);
	}
	readl(intel_private.gtt+i-1);

	return 0;
}