#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vm_offset_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  int32_t ;
typedef  TYPE_2__* c_segment_t ;
typedef  scalar_t__ boolean_t ;
struct TYPE_12__ {int /*<<< orphan*/ * c_buffer; int /*<<< orphan*/  c_swap_handle; } ;
struct TYPE_13__ {int c_busy_swapping; scalar_t__ cseg_swap_size; scalar_t__ cseg_hash; int /*<<< orphan*/  c_lock; int /*<<< orphan*/  c_bytes_used; TYPE_1__ c_store; int /*<<< orphan*/  c_mysegno; int /*<<< orphan*/  c_populated_offset; } ;

/* Variables and functions */
 scalar_t__ C_SEG_BUFFER_ADDRESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  C_SEG_BUSY (TYPE_2__*) ; 
 int /*<<< orphan*/  C_SEG_IS_ONDISK (TYPE_2__*) ; 
 int /*<<< orphan*/  C_SEG_OFFSET_TO_BYTES (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  C_SEG_WAKEUP_DONE (TYPE_2__*) ; 
 scalar_t__ FALSE ; 
 scalar_t__ KERN_SUCCESS ; 
 int /*<<< orphan*/  KMA_COMPRESSOR ; 
 int /*<<< orphan*/  OSAddAtomic64 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PAGE_REPLACEMENT_DISALLOWED (scalar_t__) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  VM_KERN_MEMORY_COMPRESSOR ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 scalar_t__ c_seg_minor_compaction_and_unlock (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  c_seg_swapin_requeue (TYPE_2__*,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  c_seg_trim_tail (TYPE_2__*) ; 
 int /*<<< orphan*/  clear_thread_rwlock_boost () ; 
 int /*<<< orphan*/  compressor_bytes_used ; 
 int /*<<< orphan*/  compressor_map ; 
 int /*<<< orphan*/  kernel_memory_depopulate (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kernel_memory_populate (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_lock_spin_always (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_unlock_always (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  panic (char*) ; 
 scalar_t__ round_page_32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_thread_rwlock_boost () ; 
 int /*<<< orphan*/  vm_swap_decrypt (TYPE_2__*) ; 
 scalar_t__ vm_swap_get (TYPE_2__*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ vmc_hash (char*,int) ; 

int
c_seg_swapin(c_segment_t c_seg, boolean_t force_minor_compaction, boolean_t age_on_swapin_q)
{
	vm_offset_t	addr = 0;
	uint32_t	io_size = 0;
	uint64_t	f_offset;

	assert(C_SEG_IS_ONDISK(c_seg));
	
#if !CHECKSUM_THE_SWAP
	c_seg_trim_tail(c_seg);
#endif
	io_size = round_page_32(C_SEG_OFFSET_TO_BYTES(c_seg->c_populated_offset));
	f_offset = c_seg->c_store.c_swap_handle;

	C_SEG_BUSY(c_seg);
	c_seg->c_busy_swapping = 1;

	/*
	 * This thread is likely going to block for I/O.
	 * Make sure it is ready to run when the I/O completes because
	 * it needs to clear the busy bit on the c_seg so that other
	 * waiting threads can make progress too. To do that, boost
	 * the rwlock_count so that the priority is boosted.
	 */
	set_thread_rwlock_boost();
	lck_mtx_unlock_always(&c_seg->c_lock);

	PAGE_REPLACEMENT_DISALLOWED(FALSE);

	addr = (vm_offset_t)C_SEG_BUFFER_ADDRESS(c_seg->c_mysegno);
	c_seg->c_store.c_buffer = (int32_t*) addr;

	kernel_memory_populate(compressor_map, addr, io_size, KMA_COMPRESSOR, VM_KERN_MEMORY_COMPRESSOR);

	if (vm_swap_get(c_seg, f_offset, io_size) != KERN_SUCCESS) {
		PAGE_REPLACEMENT_DISALLOWED(TRUE);

		kernel_memory_depopulate(compressor_map, addr, io_size, KMA_COMPRESSOR);

		c_seg_swapin_requeue(c_seg, FALSE, TRUE, age_on_swapin_q);
	} else {
#if ENCRYPTED_SWAP
		vm_swap_decrypt(c_seg);
#endif /* ENCRYPTED_SWAP */

#if CHECKSUM_THE_SWAP
		if (c_seg->cseg_swap_size != io_size)
			panic("swapin size doesn't match swapout size");

		if (c_seg->cseg_hash != vmc_hash((char*) c_seg->c_store.c_buffer, (int)io_size)) {
			panic("c_seg_swapin - Swap hash mismatch\n");
		}
#endif /* CHECKSUM_THE_SWAP */

		PAGE_REPLACEMENT_DISALLOWED(TRUE);

		c_seg_swapin_requeue(c_seg, TRUE, force_minor_compaction == TRUE ? FALSE : TRUE, age_on_swapin_q);

		OSAddAtomic64(c_seg->c_bytes_used, &compressor_bytes_used);

		if (force_minor_compaction == TRUE) {
			if (c_seg_minor_compaction_and_unlock(c_seg, FALSE)) {
				/*
				 * c_seg was completely empty so it was freed,
				 * so be careful not to reference it again
				 *
				 * Drop the rwlock_count so that the thread priority
				 * is returned back to where it is supposed to be.
				 */
				clear_thread_rwlock_boost();
				return (1);
			}

			lck_mtx_lock_spin_always(&c_seg->c_lock);
		}
	}
	C_SEG_WAKEUP_DONE(c_seg);

	/*
	 * Drop the rwlock_count so that the thread priority
	 * is returned back to where it is supposed to be.
	 */
	clear_thread_rwlock_boost();

	return (0);
}