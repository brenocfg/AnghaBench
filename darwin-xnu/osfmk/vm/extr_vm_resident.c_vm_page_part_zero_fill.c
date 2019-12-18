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
typedef  scalar_t__ vm_size_t ;
typedef  scalar_t__ vm_page_t ;
typedef  scalar_t__ vm_offset_t ;

/* Variables and functions */
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  THREAD_UNINT ; 
 int /*<<< orphan*/  VM_PAGE_CHECK (scalar_t__) ; 
 int /*<<< orphan*/  VM_PAGE_FREE (scalar_t__) ; 
 int /*<<< orphan*/  VM_PAGE_GET_PHYS_PAGE (scalar_t__) ; 
 scalar_t__ VM_PAGE_NULL ; 
 int /*<<< orphan*/  pmap_zero_part_page (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  vm_page_copy (scalar_t__,scalar_t__) ; 
 scalar_t__ vm_page_grab () ; 
 int /*<<< orphan*/  vm_page_part_copy (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  vm_page_wait (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_page_zero_fill (scalar_t__) ; 

void
vm_page_part_zero_fill(
	vm_page_t	m,
	vm_offset_t	m_pa,
	vm_size_t	len)
{

#if 0
	/*
	 * we don't hold the page queue lock
	 * so this check isn't safe to make
	 */
	VM_PAGE_CHECK(m);
#endif

#ifdef PMAP_ZERO_PART_PAGE_IMPLEMENTED
	pmap_zero_part_page(VM_PAGE_GET_PHYS_PAGE(m), m_pa, len);
#else
	vm_page_t	tmp;
	while (1) {
       		tmp = vm_page_grab();
		if (tmp == VM_PAGE_NULL) {
			vm_page_wait(THREAD_UNINT);
			continue;
		}
		break;  
	}
	vm_page_zero_fill(tmp);
	if(m_pa != 0) {
		vm_page_part_copy(m, 0, tmp, 0, m_pa);
	}
	if((m_pa + len) <  PAGE_SIZE) {
		vm_page_part_copy(m, m_pa + len, tmp, 
				m_pa + len, PAGE_SIZE - (m_pa + len));
	}
	vm_page_copy(tmp,m);
	VM_PAGE_FREE(tmp); 
#endif

}