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
struct intmem_allocation {int /*<<< orphan*/  entry; int /*<<< orphan*/  status; scalar_t__ offset; scalar_t__ size; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ MEM_INTMEM_SIZE ; 
 scalar_t__ MEM_INTMEM_START ; 
 scalar_t__ RESERVED_SIZE ; 
 int /*<<< orphan*/  STATUS_FREE ; 
 int /*<<< orphan*/  intmem_allocations ; 
 int /*<<< orphan*/  intmem_virtual ; 
 int /*<<< orphan*/  ioremap (scalar_t__,scalar_t__) ; 
 scalar_t__ kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void crisv32_intmem_init(void)
{
	static int initiated = 0;
	if (!initiated) {
		struct intmem_allocation* alloc =
		  (struct intmem_allocation*)kmalloc(sizeof *alloc, GFP_KERNEL);
		INIT_LIST_HEAD(&intmem_allocations);
		intmem_virtual = ioremap(MEM_INTMEM_START + RESERVED_SIZE,
					 MEM_INTMEM_SIZE - RESERVED_SIZE);
		initiated = 1;
		alloc->size = MEM_INTMEM_SIZE - RESERVED_SIZE;
		alloc->offset = 0;
		alloc->status = STATUS_FREE;
		list_add_tail(&alloc->entry, &intmem_allocations);
	}
}