#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vm_page_t ;
typedef  TYPE_2__* vm_object_t ;
struct TYPE_14__ {scalar_t__ code_signed; } ;
struct TYPE_13__ {int /*<<< orphan*/  vmp_error; scalar_t__ vmp_cs_tainted; int /*<<< orphan*/  vmp_offset; } ;

/* Variables and functions */
 TYPE_2__* VM_OBJECT_NULL ; 
 int /*<<< orphan*/  VM_PAGE_GET_PHYS_PAGE (TYPE_1__*) ; 
 TYPE_2__* VM_PAGE_OBJECT (TYPE_1__*) ; 
 int /*<<< orphan*/  XPR (int /*<<< orphan*/ ,char*,TYPE_2__*,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XPR_VM_PAGE ; 
 int /*<<< orphan*/  pmap_copy_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_object_lock_assert_held (TYPE_2__*) ; 
 int /*<<< orphan*/  vm_page_copy_cs_tainted ; 
 int /*<<< orphan*/  vm_page_copy_cs_validations ; 
 int /*<<< orphan*/  vm_page_validate_cs (TYPE_1__*) ; 

void
vm_page_copy(
	vm_page_t	src_m,
	vm_page_t	dest_m)
{
	vm_object_t	src_m_object;

	src_m_object = VM_PAGE_OBJECT(src_m);

        XPR(XPR_VM_PAGE,
	    "vm_page_copy, object 0x%X offset 0x%X to object 0x%X offset 0x%X\n",
	    src_m_object, src_m->vmp_offset, 
	    VM_PAGE_OBJECT(dest_m), dest_m->vmp_offset,
	    0);
#if 0
	/*
	 * we don't hold the page queue lock
	 * so this check isn't safe to make
	 */
	VM_PAGE_CHECK(src_m);
	VM_PAGE_CHECK(dest_m);
#endif
	vm_object_lock_assert_held(src_m_object);

	if (src_m_object != VM_OBJECT_NULL &&
	    src_m_object->code_signed) {
		/*
		 * We're copying a page from a code-signed object.
		 * Whoever ends up mapping the copy page might care about
		 * the original page's integrity, so let's validate the
		 * source page now.
		 */
		vm_page_copy_cs_validations++;
		vm_page_validate_cs(src_m);
#if DEVELOPMENT || DEBUG
		DTRACE_VM4(codesigned_copy,
			   vm_object_t, src_m_object,
			   vm_object_offset_t, src_m->vmp_offset,
			   int, src_m->vmp_cs_validated,
			   int, src_m->vmp_cs_tainted);
#endif /* DEVELOPMENT || DEBUG */

	}

	/*
	 * Propagate the cs_tainted bit to the copy page. Do not propagate
	 * the cs_validated bit.
	 */
	dest_m->vmp_cs_tainted = src_m->vmp_cs_tainted;
	if (dest_m->vmp_cs_tainted) {
		vm_page_copy_cs_tainted++;
	}
	dest_m->vmp_error = src_m->vmp_error; /* sliding src_m might have failed... */
	pmap_copy_page(VM_PAGE_GET_PHYS_PAGE(src_m), VM_PAGE_GET_PHYS_PAGE(dest_m));
}