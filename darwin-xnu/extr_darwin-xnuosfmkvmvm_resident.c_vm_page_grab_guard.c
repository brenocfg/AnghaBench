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
typedef  scalar_t__ vm_page_t ;

/* Variables and functions */
 int /*<<< orphan*/  OSAddAtomic (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vm_guard_count ; 
 scalar_t__ vm_page_grab_fictitious_common (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_page_guard_addr ; 

vm_page_t
vm_page_grab_guard(void)
{
	vm_page_t page;
	page = vm_page_grab_fictitious_common(vm_page_guard_addr);
    if (page) OSAddAtomic(1, &vm_guard_count);
	return page;
}