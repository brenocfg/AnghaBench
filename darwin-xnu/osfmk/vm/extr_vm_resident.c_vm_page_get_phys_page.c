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
typedef  int /*<<< orphan*/  vm_page_t ;
typedef  int /*<<< orphan*/  ppnum_t ;

/* Variables and functions */
 int /*<<< orphan*/  VM_PAGE_GET_PHYS_PAGE (int /*<<< orphan*/ ) ; 

ppnum_t
vm_page_get_phys_page(vm_page_t page)
{
	return (VM_PAGE_GET_PHYS_PAGE(page));
}