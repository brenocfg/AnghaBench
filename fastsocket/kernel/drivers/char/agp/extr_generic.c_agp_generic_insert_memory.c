#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct agp_memory {int page_count; int type; int is_flushed; int /*<<< orphan*/ * pages; struct agp_bridge_data* bridge; } ;
struct agp_bridge_data {TYPE_1__* driver; scalar_t__ gatt_table; void* current_size; } ;
typedef  int off_t ;
struct TYPE_10__ {int num_entries; } ;
struct TYPE_9__ {int num_entries; } ;
struct TYPE_8__ {int num_entries; } ;
struct TYPE_7__ {int num_entries; } ;
struct TYPE_6__ {int size_type; int (* agp_type_to_mask_type ) (struct agp_bridge_data*,int) ;int /*<<< orphan*/  (* tlb_flush ) (struct agp_memory*) ;int /*<<< orphan*/  (* mask_memory ) (struct agp_bridge_data*,int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  (* cache_flush ) () ;} ;

/* Variables and functions */
 TYPE_5__* A_SIZE_16 (void*) ; 
 TYPE_4__* A_SIZE_32 (void*) ; 
 TYPE_3__* A_SIZE_8 (void*) ; 
 TYPE_2__* A_SIZE_FIX (void*) ; 
 int EBUSY ; 
 int EINVAL ; 
#define  FIXED_APER_SIZE 132 
#define  LVL2_APER_SIZE 131 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  PGE_EMPTY (struct agp_bridge_data*,int /*<<< orphan*/ ) ; 
#define  U16_APER_SIZE 130 
#define  U32_APER_SIZE 129 
#define  U8_APER_SIZE 128 
 int agp_memory_reserved ; 
 int /*<<< orphan*/  page_to_phys (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int stub1 (struct agp_bridge_data*,int) ; 
 int /*<<< orphan*/  stub2 () ; 
 int /*<<< orphan*/  stub3 (struct agp_bridge_data*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub4 (struct agp_memory*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

int agp_generic_insert_memory(struct agp_memory * mem, off_t pg_start, int type)
{
	int num_entries;
	size_t i;
	off_t j;
	void *temp;
	struct agp_bridge_data *bridge;
	int mask_type;

	bridge = mem->bridge;
	if (!bridge)
		return -EINVAL;

	if (mem->page_count == 0)
		return 0;

	temp = bridge->current_size;

	switch (bridge->driver->size_type) {
	case U8_APER_SIZE:
		num_entries = A_SIZE_8(temp)->num_entries;
		break;
	case U16_APER_SIZE:
		num_entries = A_SIZE_16(temp)->num_entries;
		break;
	case U32_APER_SIZE:
		num_entries = A_SIZE_32(temp)->num_entries;
		break;
	case FIXED_APER_SIZE:
		num_entries = A_SIZE_FIX(temp)->num_entries;
		break;
	case LVL2_APER_SIZE:
		/* The generic routines can't deal with 2 level gatt's */
		return -EINVAL;
		break;
	default:
		num_entries = 0;
		break;
	}

	num_entries -= agp_memory_reserved/PAGE_SIZE;
	if (num_entries < 0) num_entries = 0;

	if (type != mem->type)
		return -EINVAL;

	mask_type = bridge->driver->agp_type_to_mask_type(bridge, type);
	if (mask_type != 0) {
		/* The generic routines know nothing of memory types */
		return -EINVAL;
	}

	if (((pg_start + mem->page_count) > num_entries) ||
	    ((pg_start + mem->page_count) < pg_start))
		return -EINVAL;

	j = pg_start;

	while (j < (pg_start + mem->page_count)) {
		if (!PGE_EMPTY(bridge, readl(bridge->gatt_table+j)))
			return -EBUSY;
		j++;
	}

	if (!mem->is_flushed) {
		bridge->driver->cache_flush();
		mem->is_flushed = true;
	}

	for (i = 0, j = pg_start; i < mem->page_count; i++, j++) {
		writel(bridge->driver->mask_memory(bridge,
						   page_to_phys(mem->pages[i]),
						   mask_type),
		       bridge->gatt_table+j);
	}
	readl(bridge->gatt_table+j-1);	/* PCI Posting. */

	bridge->driver->tlb_flush(mem);
	return 0;
}