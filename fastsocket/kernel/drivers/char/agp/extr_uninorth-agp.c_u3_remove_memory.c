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
typedef  scalar_t__ u32 ;
struct agp_memory {scalar_t__ type; size_t page_count; } ;
typedef  size_t off_t ;
struct TYPE_2__ {int /*<<< orphan*/ * gatt_table; } ;

/* Variables and functions */
 int EINVAL ; 
 TYPE_1__* agp_bridge ; 
 int /*<<< orphan*/  mb () ; 
 int /*<<< orphan*/  uninorth_tlbflush (struct agp_memory*) ; 

int u3_remove_memory(struct agp_memory *mem, off_t pg_start, int type)
{
	size_t i;
	u32 *gp;

	if (type != 0 || mem->type != 0)
		/* We know nothing of memory types */
		return -EINVAL;

	gp = (u32 *) &agp_bridge->gatt_table[pg_start];
	for (i = 0; i < mem->page_count; ++i)
		gp[i] = 0;
	mb();
	uninorth_tlbflush(mem);

	return 0;
}