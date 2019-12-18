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
struct page {int dummy; } ;
struct agp_bridge_data {scalar_t__ gatt_bus_addr; int /*<<< orphan*/ * gatt_table_real; int /*<<< orphan*/ * gatt_table; TYPE_1__* driver; void* current_size; } ;
struct TYPE_10__ {int page_order; } ;
struct TYPE_9__ {int page_order; } ;
struct TYPE_8__ {int page_order; } ;
struct TYPE_7__ {int page_order; } ;
struct TYPE_6__ {int size_type; } ;

/* Variables and functions */
 TYPE_5__* A_SIZE_16 (void*) ; 
 TYPE_4__* A_SIZE_32 (void*) ; 
 TYPE_3__* A_SIZE_8 (void*) ; 
 TYPE_2__* A_SIZE_FIX (void*) ; 
 int /*<<< orphan*/  ClearPageReserved (struct page*) ; 
 int EINVAL ; 
#define  FIXED_APER_SIZE 132 
#define  LVL2_APER_SIZE 131 
 int PAGE_SIZE ; 
#define  U16_APER_SIZE 130 
#define  U32_APER_SIZE 129 
#define  U8_APER_SIZE 128 
 int /*<<< orphan*/ * agp_gatt_table ; 
 int /*<<< orphan*/  free_gatt_pages (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_memory_wb (unsigned long,int) ; 
 struct page* virt_to_page (char*) ; 

int agp_generic_free_gatt_table(struct agp_bridge_data *bridge)
{
	int page_order;
	char *table, *table_end;
	void *temp;
	struct page *page;

	temp = bridge->current_size;

	switch (bridge->driver->size_type) {
	case U8_APER_SIZE:
		page_order = A_SIZE_8(temp)->page_order;
		break;
	case U16_APER_SIZE:
		page_order = A_SIZE_16(temp)->page_order;
		break;
	case U32_APER_SIZE:
		page_order = A_SIZE_32(temp)->page_order;
		break;
	case FIXED_APER_SIZE:
		page_order = A_SIZE_FIX(temp)->page_order;
		break;
	case LVL2_APER_SIZE:
		/* The generic routines can't deal with 2 level gatt's */
		return -EINVAL;
		break;
	default:
		page_order = 0;
		break;
	}

	/* Do not worry about freeing memory, because if this is
	 * called, then all agp memory is deallocated and removed
	 * from the table. */

#ifdef CONFIG_X86
	set_memory_wb((unsigned long)bridge->gatt_table, 1 << page_order);
#else
	iounmap(bridge->gatt_table);
#endif
	table = (char *) bridge->gatt_table_real;
	table_end = table + ((PAGE_SIZE * (1 << page_order)) - 1);

	for (page = virt_to_page(table); page <= virt_to_page(table_end); page++)
		ClearPageReserved(page);

	free_gatt_pages(bridge->gatt_table_real, page_order);

	agp_gatt_table = NULL;
	bridge->gatt_table = NULL;
	bridge->gatt_table_real = NULL;
	bridge->gatt_bus_addr = 0;

	return 0;
}