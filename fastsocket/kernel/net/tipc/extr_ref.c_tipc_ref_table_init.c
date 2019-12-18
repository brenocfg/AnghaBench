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
typedef  int u32 ;
struct reference {int dummy; } ;
struct TYPE_2__ {int capacity; int init_point; int index_mask; int start_mask; scalar_t__ last_free; scalar_t__ first_free; struct reference* entries; } ;

/* Variables and functions */
 int ENOMEM ; 
 int GFP_KERNEL ; 
 int /*<<< orphan*/  PAGE_KERNEL ; 
 int __GFP_HIGHMEM ; 
 int __GFP_ZERO ; 
 struct reference* __vmalloc (int,int,int /*<<< orphan*/ ) ; 
 TYPE_1__ tipc_ref_table ; 

int tipc_ref_table_init(u32 requested_size, u32 start)
{
	struct reference *table;
	u32 actual_size;

	/* account for unused entry, then round up size to a power of 2 */

	requested_size++;
	for (actual_size = 16; actual_size < requested_size; actual_size <<= 1)
		/* do nothing */ ;

	/* allocate table & mark all entries as uninitialized */

	table = __vmalloc(actual_size * sizeof(struct reference),
			  GFP_KERNEL | __GFP_HIGHMEM | __GFP_ZERO, PAGE_KERNEL);
	if (table == NULL)
		return -ENOMEM;

	tipc_ref_table.entries = table;
	tipc_ref_table.capacity = requested_size;
	tipc_ref_table.init_point = 1;
	tipc_ref_table.first_free = 0;
	tipc_ref_table.last_free = 0;
	tipc_ref_table.index_mask = actual_size - 1;
	tipc_ref_table.start_mask = start & ~tipc_ref_table.index_mask;

	return 0;
}