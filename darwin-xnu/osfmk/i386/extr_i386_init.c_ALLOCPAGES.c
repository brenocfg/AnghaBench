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

/* Variables and functions */
 uintptr_t LOW_4GB_MASK ; 
 int PAGE_SIZE ; 
 uintptr_t VM_MIN_KERNEL_ADDRESS ; 
 int /*<<< orphan*/  bzero (int,int) ; 
 int physfree ; 

__attribute__((used)) static void *
ALLOCPAGES(int npages)
{
	uintptr_t tmp = (uintptr_t)physfree;
	bzero(physfree, npages * PAGE_SIZE);
	physfree += npages * PAGE_SIZE;
	tmp += VM_MIN_KERNEL_ADDRESS & ~LOW_4GB_MASK;
	return (void *)tmp;
}