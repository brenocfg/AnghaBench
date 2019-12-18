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
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int PAGE_SIZE_64 ; 
 int /*<<< orphan*/  kernel_map ; 
 scalar_t__ kmapoff_kaddr ; 
 int kmapoff_pgcnt ; 
 int /*<<< orphan*/  vm_deallocate (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  zone_gc (int /*<<< orphan*/ ) ; 
 scalar_t__ zone_gc_allowed ; 

void
consider_zone_gc(boolean_t consider_jetsams)
{
	if (kmapoff_kaddr != 0) {
		/*
		 * One-time reclaim of kernel_map resources we allocated in
		 * early boot.
		 */
		(void) vm_deallocate(kernel_map,
		    kmapoff_kaddr, kmapoff_pgcnt * PAGE_SIZE_64);
		kmapoff_kaddr = 0;
	}

	if (zone_gc_allowed)
		zone_gc(consider_jetsams);
}