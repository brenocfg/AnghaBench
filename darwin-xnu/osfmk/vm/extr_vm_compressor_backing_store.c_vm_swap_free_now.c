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
typedef  int uint64_t ;
struct swapfile {int swp_flags; int* swp_bitmap; unsigned int swp_free_hint; int /*<<< orphan*/  swp_nseginuse; int /*<<< orphan*/ ** swp_csegs; } ;
typedef  int /*<<< orphan*/  event_t ;

/* Variables and functions */
 int COMPRESSED_SWAP_CHUNK_SIZE ; 
 int SWAP_READY ; 
 int SWAP_RECLAIM ; 
 int SWAP_SLOT_MASK ; 
 scalar_t__ VM_SWAP_SHOULD_RECLAIM () ; 
 int /*<<< orphan*/  thread_wakeup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_swapfile_gc_needed ; 
 int /*<<< orphan*/  vm_swapfile_gc_thread_running ; 
 int /*<<< orphan*/  vm_swapfile_total_segs_used ; 

__attribute__((used)) static void
vm_swap_free_now(struct swapfile *swf, uint64_t f_offset)
{
	uint64_t	file_offset = 0;
	unsigned int	segidx = 0;


	if ((swf->swp_flags & SWAP_READY) || (swf->swp_flags & SWAP_RECLAIM)) {

		unsigned int byte_for_segidx = 0;
		unsigned int offset_within_byte = 0;

		file_offset = (f_offset & SWAP_SLOT_MASK);
		segidx = (unsigned int) (file_offset / COMPRESSED_SWAP_CHUNK_SIZE);
			
		byte_for_segidx = segidx >> 3;
		offset_within_byte = segidx % 8;

		if ((swf->swp_bitmap)[byte_for_segidx] & (1 << offset_within_byte)) {
				
			(swf->swp_bitmap)[byte_for_segidx] &= ~(1 << offset_within_byte);

			swf->swp_csegs[segidx] = NULL;

			swf->swp_nseginuse--;
			vm_swapfile_total_segs_used--;

			if (segidx < swf->swp_free_hint) {
				swf->swp_free_hint = segidx;
			}
		}
		if (VM_SWAP_SHOULD_RECLAIM() && !vm_swapfile_gc_thread_running)
			thread_wakeup((event_t) &vm_swapfile_gc_needed);
	}
}