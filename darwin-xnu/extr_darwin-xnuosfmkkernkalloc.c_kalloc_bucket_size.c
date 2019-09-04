#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* zone_t ;
typedef  scalar_t__ vm_size_t ;
typedef  int /*<<< orphan*/  vm_map_t ;
struct TYPE_4__ {scalar_t__ elem_size; } ;

/* Variables and functions */
 scalar_t__ MAX_SIZE_ZDLUT ; 
 int /*<<< orphan*/  VM_MAP_PAGE_MASK (int /*<<< orphan*/ ) ; 
 TYPE_1__* get_zone_dlut (scalar_t__) ; 
 TYPE_1__* get_zone_search (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  k_zindex_start ; 
 scalar_t__ kalloc_kernmap_size ; 
 int /*<<< orphan*/  kalloc_map ; 
 scalar_t__ kalloc_max_prerounded ; 
 int /*<<< orphan*/  kernel_map ; 
 scalar_t__ vm_map_round_page (scalar_t__,int /*<<< orphan*/ ) ; 

vm_size_t
kalloc_bucket_size(
		vm_size_t 	size)
{
	zone_t 		z;
	vm_map_t 	map;
	
	if (size < MAX_SIZE_ZDLUT) {
		z = get_zone_dlut(size);
		return z->elem_size;
	} 
	
	if (size < kalloc_max_prerounded) {
		z = get_zone_search(size, k_zindex_start);
		return z->elem_size;
	}

	if (size >= kalloc_kernmap_size) 
		map = kernel_map;
	else
		map = kalloc_map;
	
	return vm_map_round_page(size, VM_MAP_PAGE_MASK(map));
}