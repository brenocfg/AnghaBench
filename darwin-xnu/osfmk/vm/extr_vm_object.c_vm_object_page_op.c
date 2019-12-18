#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vm_page_t ;
typedef  TYPE_2__* vm_object_t ;
typedef  int /*<<< orphan*/  vm_object_offset_t ;
typedef  int /*<<< orphan*/  ppnum_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
struct TYPE_16__ {int vo_shadow_offset; scalar_t__ phys_contiguous; } ;
struct TYPE_15__ {int vmp_busy; scalar_t__ vmp_pmapped; void* vmp_absent; void* vmp_precious; void* vmp_free_when_done; void* vmp_dirty; scalar_t__ vmp_cleaning; } ;

/* Variables and functions */
 void* FALSE ; 
 int /*<<< orphan*/  KERN_FAILURE ; 
 int /*<<< orphan*/  KERN_INVALID_OBJECT ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  PAGE_SLEEP (TYPE_2__*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PAGE_WAKEUP (TYPE_1__*) ; 
 int /*<<< orphan*/  SET_PAGE_DIRTY (TYPE_1__*,void*) ; 
 int /*<<< orphan*/  THREAD_UNINT ; 
 scalar_t__ TRUE ; 
 int UPL_POP_ABSENT ; 
 int UPL_POP_BUSY ; 
 int UPL_POP_CLR ; 
 int UPL_POP_DIRTY ; 
 int UPL_POP_DUMP ; 
 int UPL_POP_PAGEOUT ; 
 int UPL_POP_PHYSICAL ; 
 int UPL_POP_PRECIOUS ; 
 int UPL_POP_SET ; 
 int /*<<< orphan*/  VM_PAGE_FREE (TYPE_1__*) ; 
 int /*<<< orphan*/  VM_PAGE_GET_PHYS_PAGE (TYPE_1__*) ; 
 TYPE_1__* VM_PAGE_NULL ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  pmap_disconnect (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_object_lock (TYPE_2__*) ; 
 int /*<<< orphan*/  vm_object_unlock (TYPE_2__*) ; 
 TYPE_1__* vm_page_lookup (TYPE_2__*,int /*<<< orphan*/ ) ; 

kern_return_t
vm_object_page_op(
	vm_object_t		object,
	vm_object_offset_t	offset,
	int			ops,
	ppnum_t			*phys_entry,
	int			*flags)
{
	vm_page_t		dst_page;

	vm_object_lock(object);

	if(ops & UPL_POP_PHYSICAL) {
		if(object->phys_contiguous) {
			if (phys_entry) {
				*phys_entry = (ppnum_t)
					(object->vo_shadow_offset >> PAGE_SHIFT);
			}
			vm_object_unlock(object);
			return KERN_SUCCESS;
		} else {
			vm_object_unlock(object);
			return KERN_INVALID_OBJECT;
		}
	}
	if(object->phys_contiguous) {
		vm_object_unlock(object);
		return KERN_INVALID_OBJECT;
	}

	while(TRUE) {
		if((dst_page = vm_page_lookup(object,offset)) == VM_PAGE_NULL) {
			vm_object_unlock(object);
			return KERN_FAILURE;
		}

		/* Sync up on getting the busy bit */
		if((dst_page->vmp_busy || dst_page->vmp_cleaning) && 
			   (((ops & UPL_POP_SET) && 
			   (ops & UPL_POP_BUSY)) || (ops & UPL_POP_DUMP))) {
			/* someone else is playing with the page, we will */
			/* have to wait */
			PAGE_SLEEP(object, dst_page, THREAD_UNINT);
			continue;
		}

		if (ops & UPL_POP_DUMP) {
			if (dst_page->vmp_pmapped == TRUE)
			        pmap_disconnect(VM_PAGE_GET_PHYS_PAGE(dst_page));

			VM_PAGE_FREE(dst_page);
			break;
		}

		if (flags) {
		        *flags = 0;

			/* Get the condition of flags before requested ops */
			/* are undertaken */

			if(dst_page->vmp_dirty) *flags |= UPL_POP_DIRTY;
			if(dst_page->vmp_free_when_done) *flags |= UPL_POP_PAGEOUT;
			if(dst_page->vmp_precious) *flags |= UPL_POP_PRECIOUS;
			if(dst_page->vmp_absent) *flags |= UPL_POP_ABSENT;
			if(dst_page->vmp_busy) *flags |= UPL_POP_BUSY;
		}

		/* The caller should have made a call either contingent with */
		/* or prior to this call to set UPL_POP_BUSY */
		if(ops & UPL_POP_SET) {
			/* The protection granted with this assert will */
			/* not be complete.  If the caller violates the */
			/* convention and attempts to change page state */
			/* without first setting busy we may not see it */
			/* because the page may already be busy.  However */
			/* if such violations occur we will assert sooner */
			/* or later. */
			assert(dst_page->vmp_busy || (ops & UPL_POP_BUSY));
			if (ops & UPL_POP_DIRTY) {
				SET_PAGE_DIRTY(dst_page, FALSE);
			}
			if (ops & UPL_POP_PAGEOUT) dst_page->vmp_free_when_done = TRUE;
			if (ops & UPL_POP_PRECIOUS) dst_page->vmp_precious = TRUE;
			if (ops & UPL_POP_ABSENT) dst_page->vmp_absent = TRUE;
			if (ops & UPL_POP_BUSY) dst_page->vmp_busy = TRUE;
		}

		if(ops & UPL_POP_CLR) {
			assert(dst_page->vmp_busy);
			if (ops & UPL_POP_DIRTY) dst_page->vmp_dirty = FALSE;
			if (ops & UPL_POP_PAGEOUT) dst_page->vmp_free_when_done = FALSE;
			if (ops & UPL_POP_PRECIOUS) dst_page->vmp_precious = FALSE;
			if (ops & UPL_POP_ABSENT) dst_page->vmp_absent = FALSE;
			if (ops & UPL_POP_BUSY) {
			        dst_page->vmp_busy = FALSE;
				PAGE_WAKEUP(dst_page);
			}
		}
		if (phys_entry) {
			/*
			 * The physical page number will remain valid
			 * only if the page is kept busy.
			 */
			assert(dst_page->vmp_busy);
			*phys_entry = VM_PAGE_GET_PHYS_PAGE(dst_page);
		}

		break;
	}

	vm_object_unlock(object);
	return KERN_SUCCESS;
				
}