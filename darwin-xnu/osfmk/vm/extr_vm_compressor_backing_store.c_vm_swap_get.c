#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
struct swapfile {int swp_flags; scalar_t__ swp_io_count; int /*<<< orphan*/  swp_vp; } ;
typedef  int /*<<< orphan*/  kern_return_t ;
typedef  int /*<<< orphan*/  event_t ;
typedef  TYPE_2__* c_segment_t ;
struct TYPE_6__ {scalar_t__ c_buffer; } ;
struct TYPE_7__ {TYPE_1__ c_store; } ;

/* Variables and functions */
 int /*<<< orphan*/  C_SEG_MAKE_WRITEABLE (TYPE_2__*) ; 
 int /*<<< orphan*/  C_SEG_WRITE_PROTECT (TYPE_2__*) ; 
 int /*<<< orphan*/  KERN_FAILURE ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 int PAGE_SHIFT ; 
 int PAGE_SIZE_64 ; 
 int /*<<< orphan*/  SWAP_READ ; 
 int SWAP_READY ; 
 int SWAP_RECLAIM ; 
 int SWAP_SLOT_MASK ; 
 int SWAP_WANTED ; 
 int /*<<< orphan*/  VM_STAT_INCR_BY (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  assert (scalar_t__) ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  swapins ; 
 int /*<<< orphan*/  thread_wakeup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_swap_data_lock ; 
 int /*<<< orphan*/  vm_swap_free (int) ; 
 int /*<<< orphan*/  vm_swap_get_failures ; 
 struct swapfile* vm_swapfile_for_handle (int) ; 
 int vm_swapfile_io (int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

kern_return_t
vm_swap_get(c_segment_t c_seg, uint64_t f_offset, uint64_t size)
{
	struct swapfile *swf = NULL;
	uint64_t	file_offset = 0;
	int		retval = 0;

	assert(c_seg->c_store.c_buffer);

	lck_mtx_lock(&vm_swap_data_lock);

	swf = vm_swapfile_for_handle(f_offset);

	if (swf == NULL || ( !(swf->swp_flags & SWAP_READY) && !(swf->swp_flags & SWAP_RECLAIM))) {
		retval = 1;
		goto done;
	}
	swf->swp_io_count++;

	lck_mtx_unlock(&vm_swap_data_lock);

#if DEVELOPMENT || DEBUG
	C_SEG_MAKE_WRITEABLE(c_seg);
#endif
	file_offset = (f_offset & SWAP_SLOT_MASK);
	retval = vm_swapfile_io(swf->swp_vp, file_offset, (uint64_t)c_seg->c_store.c_buffer, (int)(size / PAGE_SIZE_64), SWAP_READ, NULL);

#if DEVELOPMENT || DEBUG
	C_SEG_WRITE_PROTECT(c_seg);
#endif
	if (retval == 0)
		VM_STAT_INCR_BY(swapins, size >> PAGE_SHIFT);
	else
		vm_swap_get_failures++;

	/*
	 * Free this slot in the swap structure.
	 */
	vm_swap_free(f_offset);

	lck_mtx_lock(&vm_swap_data_lock);
	swf->swp_io_count--;

	if ((swf->swp_flags & SWAP_WANTED) && swf->swp_io_count == 0) {
	
		swf->swp_flags &= ~SWAP_WANTED;
		thread_wakeup((event_t) &swf->swp_flags);
	}
done:
	lck_mtx_unlock(&vm_swap_data_lock);

	if (retval == 0)
		return KERN_SUCCESS;
	else
		return KERN_FAILURE;
}