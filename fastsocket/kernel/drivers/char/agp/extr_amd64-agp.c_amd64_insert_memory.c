#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  long long u32 ;
struct agp_memory {int type; unsigned long page_count; int is_flushed; int /*<<< orphan*/ * pages; struct agp_bridge_data* bridge; } ;
struct agp_bridge_data {TYPE_1__* driver; } ;
typedef  int off_t ;
struct TYPE_8__ {scalar_t__ gatt_table; TYPE_2__* driver; } ;
struct TYPE_7__ {long long (* mask_memory ) (TYPE_3__*,int /*<<< orphan*/ ,int) ;} ;
struct TYPE_6__ {int (* agp_type_to_mask_type ) (struct agp_bridge_data*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (long long) ; 
 int EBUSY ; 
 int EINVAL ; 
 long long GPTE_COHERENT ; 
 long long GPTE_VALID ; 
 int /*<<< orphan*/  PGE_EMPTY (TYPE_3__*,int /*<<< orphan*/ ) ; 
 TYPE_3__* agp_bridge ; 
 int agp_num_entries () ; 
 int /*<<< orphan*/  amd64_tlbflush (struct agp_memory*) ; 
 int /*<<< orphan*/  global_cache_flush () ; 
 int /*<<< orphan*/  page_to_phys (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int stub1 (struct agp_bridge_data*,int) ; 
 long long stub2 (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  writel (long long,scalar_t__) ; 

__attribute__((used)) static int amd64_insert_memory(struct agp_memory *mem, off_t pg_start, int type)
{
	int i, j, num_entries;
	long long tmp;
	int mask_type;
	struct agp_bridge_data *bridge = mem->bridge;
	u32 pte;

	num_entries = agp_num_entries();

	if (type != mem->type)
		return -EINVAL;
	mask_type = bridge->driver->agp_type_to_mask_type(bridge, type);
	if (mask_type != 0)
		return -EINVAL;


	/* Make sure we can fit the range in the gatt table. */
	/* FIXME: could wrap */
	if (((unsigned long)pg_start + mem->page_count) > num_entries)
		return -EINVAL;

	j = pg_start;

	/* gatt table should be empty. */
	while (j < (pg_start + mem->page_count)) {
		if (!PGE_EMPTY(agp_bridge, readl(agp_bridge->gatt_table+j)))
			return -EBUSY;
		j++;
	}

	if (!mem->is_flushed) {
		global_cache_flush();
		mem->is_flushed = true;
	}

	for (i = 0, j = pg_start; i < mem->page_count; i++, j++) {
		tmp = agp_bridge->driver->mask_memory(agp_bridge,
						      page_to_phys(mem->pages[i]),
						      mask_type);

		BUG_ON(tmp & 0xffffff0000000ffcULL);
		pte = (tmp & 0x000000ff00000000ULL) >> 28;
		pte |=(tmp & 0x00000000fffff000ULL);
		pte |= GPTE_VALID | GPTE_COHERENT;

		writel(pte, agp_bridge->gatt_table+j);
		readl(agp_bridge->gatt_table+j);	/* PCI Posting. */
	}
	amd64_tlbflush(mem);
	return 0;
}