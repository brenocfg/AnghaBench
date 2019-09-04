#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vm_offset_t ;
typedef  int uint64_t ;
typedef  int uint32_t ;
struct swapout_io_completion {int swp_c_size; int /*<<< orphan*/  swp_upl_ctx; scalar_t__ swp_io_done; scalar_t__ swp_io_error; struct swapfile* swp_swf; TYPE_1__* swp_c_seg; } ;
struct swapfile {unsigned int swp_free_hint; int swp_flags; unsigned int swp_nseginuse; unsigned int swp_nsegs; int* swp_bitmap; int swp_index; int /*<<< orphan*/  swp_vp; int /*<<< orphan*/  swp_queue; TYPE_1__** swp_csegs; int /*<<< orphan*/  swp_io_count; } ;
typedef  int /*<<< orphan*/  queue_entry_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
typedef  int /*<<< orphan*/  event_t ;
typedef  int /*<<< orphan*/  clock_sec_t ;
typedef  int /*<<< orphan*/  clock_nsec_t ;
typedef  TYPE_1__* c_segment_t ;
typedef  int boolean_t ;
struct TYPE_3__ {int c_busy_swapping; int c_busy; int /*<<< orphan*/  c_on_minorcompact_q; } ;

/* Variables and functions */
 unsigned int COMPRESSED_SWAP_CHUNK_SIZE ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  KERN_FAILURE ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 int NSEC_PER_USEC ; 
 int PAGE_SIZE_64 ; 
 int SWAP_DEVICE_SHIFT ; 
 int SWAP_READY ; 
 int /*<<< orphan*/  SWAP_WRITE ; 
 int /*<<< orphan*/  THREAD_CONTINUE_NULL ; 
 int /*<<< orphan*/  THREAD_INTERRUPTIBLE ; 
 int TRUE ; 
 scalar_t__ VM_SWAP_SHOULD_CREATE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  assert_wait_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  clock_get_system_nanotime (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ hibernate_flushing ; 
 int hibernate_no_swapspace ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ *) ; 
 int queue_end (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ queue_first (int /*<<< orphan*/ *) ; 
 scalar_t__ queue_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  swf_global_queue ; 
 int /*<<< orphan*/  thread_block (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_wakeup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_num_swap_files ; 
 int /*<<< orphan*/  vm_swap_data_lock ; 
 int /*<<< orphan*/  vm_swap_put_failures ; 
 int /*<<< orphan*/  vm_swap_put_finish (struct swapfile*,int*,int) ; 
 int /*<<< orphan*/  vm_swapfile_create_needed ; 
 int /*<<< orphan*/  vm_swapfile_create_thread_running ; 
 int vm_swapfile_io (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  vm_swapfile_total_segs_used ; 

kern_return_t
vm_swap_put(vm_offset_t addr, uint64_t *f_offset, uint32_t size, c_segment_t c_seg, struct swapout_io_completion *soc)
{
	unsigned int	segidx = 0;
	struct swapfile *swf = NULL;
	uint64_t	file_offset = 0;
	uint64_t	swapfile_index = 0;
	unsigned int 	byte_for_segidx = 0;
	unsigned int 	offset_within_byte = 0;
	boolean_t	swf_eligible = FALSE;
	boolean_t	waiting = FALSE;
	boolean_t	retried = FALSE;
	int		error = 0;
	clock_sec_t	sec;
	clock_nsec_t	nsec;
	void            *upl_ctx = NULL;

	if (addr == 0 || f_offset == NULL) {
		return KERN_FAILURE;
	}
retry:
	lck_mtx_lock(&vm_swap_data_lock);

	swf = (struct swapfile*) queue_first(&swf_global_queue);

	while(queue_end(&swf_global_queue, (queue_entry_t)swf) == FALSE) {
	
		segidx = swf->swp_free_hint;

		swf_eligible = 	(swf->swp_flags & SWAP_READY) && (swf->swp_nseginuse < swf->swp_nsegs);

		if (swf_eligible) {

			while(segidx < swf->swp_nsegs) {
				
				byte_for_segidx = segidx >> 3;
				offset_within_byte = segidx % 8;
			
				if ((swf->swp_bitmap)[byte_for_segidx] & (1 << offset_within_byte)) {
					segidx++;
					continue;
				}
		
				(swf->swp_bitmap)[byte_for_segidx] |= (1 << offset_within_byte);

				file_offset = segidx * COMPRESSED_SWAP_CHUNK_SIZE;
				swf->swp_nseginuse++;
				swf->swp_io_count++;
				swf->swp_csegs[segidx] = c_seg;

				swapfile_index = swf->swp_index;
				vm_swapfile_total_segs_used++;

				clock_get_system_nanotime(&sec, &nsec);

				if (VM_SWAP_SHOULD_CREATE(sec) && !vm_swapfile_create_thread_running)
					thread_wakeup((event_t) &vm_swapfile_create_needed);

				lck_mtx_unlock(&vm_swap_data_lock);
		
				goto issue_io;
			}
		}
		swf = (struct swapfile*) queue_next(&swf->swp_queue);
	}
	assert(queue_end(&swf_global_queue, (queue_entry_t) swf));
	
	/*
	 * we've run out of swap segments, but may not
	 * be in a position to immediately create a new swap
	 * file if we've recently failed to create due to a lack
	 * of free space in the root filesystem... we'll try
	 * to kick that create off, but in any event we're going
	 * to take a breather (up to 1 second) so that we're not caught in a tight
	 * loop back in "vm_compressor_compact_and_swap" trying to stuff
	 * segments into swap files only to have them immediately put back
	 * on the c_age queue due to vm_swap_put failing.
	 *
	 * if we're doing these puts due to a hibernation flush,
	 * no need to block... setting hibernate_no_swapspace to TRUE,
	 * will cause "vm_compressor_compact_and_swap" to immediately abort
	 */
	clock_get_system_nanotime(&sec, &nsec);

	if (VM_SWAP_SHOULD_CREATE(sec) && !vm_swapfile_create_thread_running)
		thread_wakeup((event_t) &vm_swapfile_create_needed);

	if (hibernate_flushing == FALSE || VM_SWAP_SHOULD_CREATE(sec)) {
		waiting = TRUE;
		assert_wait_timeout((event_t) &vm_num_swap_files, THREAD_INTERRUPTIBLE, 1000, 1000*NSEC_PER_USEC);
	} else
		hibernate_no_swapspace = TRUE;

	lck_mtx_unlock(&vm_swap_data_lock);

	if (waiting == TRUE) {
		thread_block(THREAD_CONTINUE_NULL);

		if (retried == FALSE && hibernate_flushing == TRUE) {
			retried = TRUE;
			goto retry;
		}
	}
	vm_swap_put_failures++;

	return KERN_FAILURE;

issue_io:	
	assert(c_seg->c_busy_swapping);
	assert(c_seg->c_busy);
	assert(!c_seg->c_on_minorcompact_q);

	*f_offset = (swapfile_index << SWAP_DEVICE_SHIFT) | file_offset;

	if (soc) {
		soc->swp_c_seg = c_seg;
		soc->swp_c_size = size;

	        soc->swp_swf = swf;

		soc->swp_io_error = 0;
		soc->swp_io_done = 0;

		upl_ctx = (void *)&soc->swp_upl_ctx;
	}
	error = vm_swapfile_io(swf->swp_vp, file_offset, addr, (int) (size / PAGE_SIZE_64), SWAP_WRITE, upl_ctx);

	if (error || upl_ctx == NULL)
		return (vm_swap_put_finish(swf, f_offset, error));

	return KERN_SUCCESS;
}