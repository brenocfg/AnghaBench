#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vm_page_t ;
struct TYPE_7__ {int /*<<< orphan*/  vmp_offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  VM_PAGE_CHECK (TYPE_1__*) ; 
 int /*<<< orphan*/  VM_PAGE_GET_PHYS_PAGE (TYPE_1__*) ; 
 int /*<<< orphan*/  VM_PAGE_OBJECT (TYPE_1__*) ; 
 int /*<<< orphan*/  XPR (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XPR_VM_PAGE ; 
 int /*<<< orphan*/  pmap_zero_page (int /*<<< orphan*/ ) ; 

void
vm_page_zero_fill(
	vm_page_t	m)
{
        XPR(XPR_VM_PAGE,
	    "vm_page_zero_fill, object 0x%X offset 0x%X page 0x%X\n",
	    VM_PAGE_OBJECT(m), m->vmp_offset, m, 0,0);
#if 0
	/*
	 * we don't hold the page queue lock
	 * so this check isn't safe to make
	 */
	VM_PAGE_CHECK(m);
#endif

//	dbgTrace(0xAEAEAEAE, VM_PAGE_GET_PHYS_PAGE(m), 0);		/* (BRINGUP) */
	pmap_zero_page(VM_PAGE_GET_PHYS_PAGE(m));
}