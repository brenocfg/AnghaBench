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
struct vm_map_links {int dummy; } ;
struct vm_map_entry {int dummy; } ;

/* Variables and functions */
 int PAGE_SIZE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  vm_map_entry_reserved_zone ; 
 int /*<<< orphan*/  vm_map_holes_zone ; 
 int /*<<< orphan*/  vm_map_supports_hole_optimization ; 
 int /*<<< orphan*/  zone_prio_refill_configure (int /*<<< orphan*/ ,int) ; 

void
vm_kernel_reserved_entry_init(void) {
	zone_prio_refill_configure(vm_map_entry_reserved_zone, (6*PAGE_SIZE)/sizeof(struct vm_map_entry));

	/*
	 * Once we have our replenish thread set up, we can start using the vm_map_holes zone.
	 */
	zone_prio_refill_configure(vm_map_holes_zone, (6*PAGE_SIZE)/sizeof(struct vm_map_links));
	vm_map_supports_hole_optimization = TRUE;
}