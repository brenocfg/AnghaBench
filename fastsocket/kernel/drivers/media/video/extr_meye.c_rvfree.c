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
 int /*<<< orphan*/  ClearPageReserved (int /*<<< orphan*/ ) ; 
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  vfree (void*) ; 
 int /*<<< orphan*/  vmalloc_to_page (void*) ; 

__attribute__((used)) static void rvfree(void * mem, unsigned long size)
{
	unsigned long adr;

	if (mem) {
		adr = (unsigned long) mem;
		while ((long) size > 0) {
			ClearPageReserved(vmalloc_to_page((void *)adr));
			adr += PAGE_SIZE;
			size -= PAGE_SIZE;
		}
		vfree(mem);
	}
}