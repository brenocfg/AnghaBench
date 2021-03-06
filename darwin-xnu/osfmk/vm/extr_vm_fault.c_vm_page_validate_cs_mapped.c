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

/* Variables and functions */
 int /*<<< orphan*/  vm_page_validate_cs_fast (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_page_validate_cs_mapped_slow (int /*<<< orphan*/ ,void const*) ; 

void
vm_page_validate_cs_mapped(
	vm_page_t	page,
	const void	*kaddr)
{
	if (!vm_page_validate_cs_fast(page)) {
		vm_page_validate_cs_mapped_slow(page, kaddr);
	}
}