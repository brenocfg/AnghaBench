#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int vm_size_t ;
typedef  int uint64_t ;
struct vm_page_with_ppnum {int dummy; } ;
struct vm_page {int dummy; } ;
struct TYPE_5__ {int count; int sum_count; int elem_size; int cur_size; int /*<<< orphan*/  page_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  OSAddAtomic64 (int,int /*<<< orphan*/ *) ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  TRUE ; 
 int VM_PACKED_POINTER_ALIGNMENT ; 
 int /*<<< orphan*/  VM_PAGE_MOVE_STOLEN (int) ; 
 int /*<<< orphan*/  Z_ALIGNMENT_REQUIRED ; 
 int /*<<< orphan*/  Z_CALLERACCT ; 
 int /*<<< orphan*/  Z_EXHAUST ; 
 int /*<<< orphan*/  Z_EXPAND ; 
 int /*<<< orphan*/  Z_FOREIGN ; 
 int /*<<< orphan*/  Z_GZALLOC_EXEMPT ; 
 int round_page (int) ; 
 TYPE_1__* vm_page_array_zone ; 
 int vm_page_pages ; 
 TYPE_1__* vm_page_zone ; 
 TYPE_1__* zinit (int,int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  zone_change (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
vm_page_module_init(void)
{
	uint64_t vm_page_zone_pages, vm_page_array_zone_data_size;
	vm_size_t	vm_page_with_ppnum_size;

	vm_page_array_zone = zinit((vm_size_t) sizeof(struct vm_page),
			     0, PAGE_SIZE, "vm pages array");

	zone_change(vm_page_array_zone, Z_CALLERACCT, FALSE);
	zone_change(vm_page_array_zone, Z_EXPAND, FALSE);
	zone_change(vm_page_array_zone, Z_EXHAUST, TRUE);
	zone_change(vm_page_array_zone, Z_FOREIGN, TRUE);
	zone_change(vm_page_array_zone, Z_GZALLOC_EXEMPT, TRUE);
	/*
	 * Adjust zone statistics to account for the real pages allocated
	 * in vm_page_create(). [Q: is this really what we want?]
	 */
	vm_page_array_zone->count += vm_page_pages;
	vm_page_array_zone->sum_count += vm_page_pages;
	vm_page_array_zone_data_size = vm_page_pages * vm_page_array_zone->elem_size;
	vm_page_array_zone->cur_size += vm_page_array_zone_data_size;
	vm_page_zone_pages = ((round_page(vm_page_array_zone_data_size)) / PAGE_SIZE);
	OSAddAtomic64(vm_page_zone_pages, &(vm_page_array_zone->page_count));
	/* since zone accounts for these, take them out of stolen */
	VM_PAGE_MOVE_STOLEN(vm_page_zone_pages);

	vm_page_with_ppnum_size = (sizeof(struct vm_page_with_ppnum) + (VM_PACKED_POINTER_ALIGNMENT-1)) & ~(VM_PACKED_POINTER_ALIGNMENT - 1);

	vm_page_zone = zinit(vm_page_with_ppnum_size,
			     0, PAGE_SIZE, "vm pages");

	zone_change(vm_page_zone, Z_CALLERACCT, FALSE);
	zone_change(vm_page_zone, Z_EXPAND, FALSE);
	zone_change(vm_page_zone, Z_EXHAUST, TRUE);
	zone_change(vm_page_zone, Z_FOREIGN, TRUE);
	zone_change(vm_page_zone, Z_GZALLOC_EXEMPT, TRUE);
	zone_change(vm_page_zone, Z_ALIGNMENT_REQUIRED, TRUE);
}