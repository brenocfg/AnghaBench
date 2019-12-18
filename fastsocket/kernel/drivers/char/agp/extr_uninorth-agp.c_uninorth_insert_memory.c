#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct agp_memory {int type; int page_count; int /*<<< orphan*/ * pages; } ;
typedef  int off_t ;
struct TYPE_7__ {int num_entries; } ;
struct TYPE_6__ {scalar_t__* gatt_table; TYPE_1__* driver; void* current_size; } ;
struct TYPE_5__ {int (* agp_type_to_mask_type ) (TYPE_2__*,int) ;} ;

/* Variables and functions */
 TYPE_4__* A_SIZE_32 (void*) ; 
 int EBUSY ; 
 int EINVAL ; 
 scalar_t__ __va (int) ; 
 TYPE_2__* agp_bridge ; 
 scalar_t__ cpu_to_le32 (int) ; 
 int /*<<< orphan*/  flush_dcache_range (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  in_le32 (int /*<<< orphan*/  volatile*) ; 
 int /*<<< orphan*/  mb () ; 
 int page_to_phys (int /*<<< orphan*/ ) ; 
 int stub1 (TYPE_2__*,int) ; 
 int /*<<< orphan*/  uninorth_tlbflush (struct agp_memory*) ; 

__attribute__((used)) static int uninorth_insert_memory(struct agp_memory *mem, off_t pg_start,
				int type)
{
	int i, j, num_entries;
	void *temp;
	int mask_type;

	temp = agp_bridge->current_size;
	num_entries = A_SIZE_32(temp)->num_entries;

	if (type != mem->type)
		return -EINVAL;

	mask_type = agp_bridge->driver->agp_type_to_mask_type(agp_bridge, type);
	if (mask_type != 0) {
		/* We know nothing of memory types */
		return -EINVAL;
	}

	if ((pg_start + mem->page_count) > num_entries)
		return -EINVAL;

	j = pg_start;

	while (j < (pg_start + mem->page_count)) {
		if (agp_bridge->gatt_table[j])
			return -EBUSY;
		j++;
	}

	for (i = 0, j = pg_start; i < mem->page_count; i++, j++) {
		agp_bridge->gatt_table[j] =
			cpu_to_le32((page_to_phys(mem->pages[i]) & 0xFFFFF000UL) | 0x1UL);
		flush_dcache_range((unsigned long)__va(page_to_phys(mem->pages[i])),
				   (unsigned long)__va(page_to_phys(mem->pages[i]))+0x1000);
	}
	(void)in_le32((volatile u32*)&agp_bridge->gatt_table[pg_start]);
	mb();

	uninorth_tlbflush(mem);
	return 0;
}