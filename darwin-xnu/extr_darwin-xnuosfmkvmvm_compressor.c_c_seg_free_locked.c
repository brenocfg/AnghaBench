#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vm_offset_t ;
typedef  scalar_t__ uint64_t ;
struct c_slot {int dummy; } ;
typedef  int /*<<< orphan*/  int32_t ;
typedef  TYPE_2__* c_segment_t ;
struct TYPE_11__ {int c_segno; } ;
struct TYPE_9__ {scalar_t__ c_swap_handle; int /*<<< orphan*/ * c_buffer; } ;
struct TYPE_10__ {int c_busy; scalar_t__ c_slots_used; scalar_t__ c_overage_swap; int c_mysegno; int c_slot_var_array_len; int /*<<< orphan*/  c_slot_var_array; int /*<<< orphan*/  c_lock; TYPE_1__ c_store; int /*<<< orphan*/  c_populated_offset; int /*<<< orphan*/  c_busy_swapping; int /*<<< orphan*/  c_on_minorcompact_q; } ;

/* Variables and functions */
 int /*<<< orphan*/  C_IS_FREE ; 
 int /*<<< orphan*/  C_SEG_IS_ONDISK (TYPE_2__*) ; 
 int /*<<< orphan*/  C_SEG_OFFSET_TO_BYTES (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  C_SEG_WAKEUP_DONE (TYPE_2__*) ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  KMA_COMPRESSOR ; 
 int PAGE_SIZE ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  assert (int) ; 
 int c_free_segno_head ; 
 int /*<<< orphan*/ * c_list_lock ; 
 int /*<<< orphan*/  c_overage_swapped_count ; 
 int /*<<< orphan*/  c_seg_switch_state (TYPE_2__*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  c_segment_count ; 
 TYPE_4__* c_segments ; 
 int /*<<< orphan*/  compressor_map ; 
 int /*<<< orphan*/  compressor_segment_zone ; 
 int /*<<< orphan*/  kernel_memory_depopulate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  lck_mtx_destroy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_lock_spin_always (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_unlock_always (int /*<<< orphan*/ *) ; 
 int round_page_32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_compressor_lck_grp ; 
 int /*<<< orphan*/  vm_swap_free (scalar_t__) ; 
 int /*<<< orphan*/  zfree (int /*<<< orphan*/ ,TYPE_2__*) ; 

void
c_seg_free_locked(c_segment_t c_seg)
{
	int		segno;
	int		pages_populated = 0;
	int32_t		*c_buffer = NULL;
	uint64_t	c_swap_handle = 0;

	assert(c_seg->c_busy);
	assert(c_seg->c_slots_used == 0);
	assert(!c_seg->c_on_minorcompact_q);
	assert(!c_seg->c_busy_swapping);

	if (c_seg->c_overage_swap == TRUE) {
		c_overage_swapped_count--;
		c_seg->c_overage_swap = FALSE;
	}	
	if ( !(C_SEG_IS_ONDISK(c_seg)))
		c_buffer = c_seg->c_store.c_buffer;
	else
		c_swap_handle = c_seg->c_store.c_swap_handle;

	c_seg_switch_state(c_seg, C_IS_FREE, FALSE);

	lck_mtx_unlock_always(c_list_lock);

	if (c_buffer) {
		pages_populated = (round_page_32(C_SEG_OFFSET_TO_BYTES(c_seg->c_populated_offset))) / PAGE_SIZE;
		c_seg->c_store.c_buffer = NULL;
	} else
		c_seg->c_store.c_swap_handle = (uint64_t)-1;

	lck_mtx_unlock_always(&c_seg->c_lock);

	if (c_buffer) {
		if (pages_populated)
			kernel_memory_depopulate(compressor_map, (vm_offset_t) c_buffer, pages_populated * PAGE_SIZE, KMA_COMPRESSOR);

	} else if (c_swap_handle) {
                /*
                 * Free swap space on disk.
		 */
		vm_swap_free(c_swap_handle);
	}
	lck_mtx_lock_spin_always(&c_seg->c_lock);
	/*
	 * c_seg must remain busy until
	 * after the call to vm_swap_free
	 */
	C_SEG_WAKEUP_DONE(c_seg);
	lck_mtx_unlock_always(&c_seg->c_lock);

	segno = c_seg->c_mysegno;

	lck_mtx_lock_spin_always(c_list_lock);
	/*
	 * because the c_buffer is now associated with the segno,
	 * we can't put the segno back on the free list until
	 * after we have depopulated the c_buffer range, or 
	 * we run the risk of depopulating a range that is 
	 * now being used in one of the compressor heads
	 */
	c_segments[segno].c_segno = c_free_segno_head;
	c_free_segno_head = segno;
	c_segment_count--;

	lck_mtx_unlock_always(c_list_lock);

	lck_mtx_destroy(&c_seg->c_lock, &vm_compressor_lck_grp);

	if (c_seg->c_slot_var_array_len)
		kfree(c_seg->c_slot_var_array, sizeof(struct c_slot) * c_seg->c_slot_var_array_len);

	zfree(compressor_segment_zone, c_seg);
}