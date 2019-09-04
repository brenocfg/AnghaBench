#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_27__   TYPE_5__ ;
typedef  struct TYPE_26__   TYPE_4__ ;
typedef  struct TYPE_25__   TYPE_3__ ;
typedef  struct TYPE_24__   TYPE_2__ ;
typedef  struct TYPE_23__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vm_offset_t ;
typedef  size_t uint32_t ;
typedef  int /*<<< orphan*/  int32_t ;
typedef  scalar_t__ clock_sec_t ;
typedef  int /*<<< orphan*/  clock_nsec_t ;
typedef  TYPE_2__* c_slot_t ;
typedef  TYPE_3__* c_slot_mapping_t ;
typedef  TYPE_4__* c_segment_t ;
typedef  scalar_t__ boolean_t ;
typedef  int /*<<< orphan*/  WK_word ;
struct TYPE_27__ {size_t c_segno; TYPE_4__* c_seg; } ;
struct TYPE_23__ {int /*<<< orphan*/ * c_buffer; } ;
struct TYPE_26__ {scalar_t__ c_state; int c_busy; int c_nextslot; scalar_t__ c_swappedin_ts; size_t c_creation_ts; int c_bytes_unused; scalar_t__ c_bytes_used; int c_slots_used; int c_firstemptyslot; int /*<<< orphan*/  c_lock; scalar_t__ c_on_minorcompact_q; TYPE_1__ c_store; int /*<<< orphan*/  c_populated_offset; scalar_t__ c_busy_swapping; } ;
struct TYPE_25__ {size_t s_cseg; int s_cindx; } ;
struct TYPE_24__ {size_t c_offset; } ;

/* Variables and functions */
 int C_DONT_BLOCK ; 
 scalar_t__ C_IS_EMPTY ; 
 scalar_t__ C_IS_FILLING ; 
 scalar_t__ C_IS_FREE ; 
 int C_KDP ; 
 int C_KEEP ; 
 scalar_t__ C_ON_BAD_Q ; 
 scalar_t__ C_ON_SWAPIO_Q ; 
 scalar_t__ C_ON_SWAPOUT_Q ; 
 scalar_t__ C_ON_SWAPPEDOUTSPARSE_Q ; 
 int /*<<< orphan*/  C_SEG_BUSY (TYPE_4__*) ; 
 int /*<<< orphan*/  C_SEG_BYTES_TO_OFFSET (int /*<<< orphan*/ ) ; 
 scalar_t__ C_SEG_IS_ONDISK (TYPE_4__*) ; 
 int /*<<< orphan*/  C_SEG_IS_ON_DISK_OR_SOQ (TYPE_4__*) ; 
 size_t C_SEG_OFFSET_ALIGNMENT_MASK ; 
 int /*<<< orphan*/  C_SEG_OFFSET_TO_BYTES (int /*<<< orphan*/ ) ; 
 scalar_t__ C_SEG_ONDISK_IS_SPARSE (TYPE_4__*) ; 
 scalar_t__ C_SEG_SHOULD_MINORCOMPACT_NOW (TYPE_4__*) ; 
 TYPE_2__* C_SEG_SLOT_FROM_INDEX (TYPE_4__*,int) ; 
 int C_SEG_UNUSED_BYTES (TYPE_4__*) ; 
 int /*<<< orphan*/  C_SEG_WAKEUP_DONE (TYPE_4__*) ; 
 size_t DECOMPRESSION_SAMPLE_MAX_AGE ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  KMA_COMPRESSOR ; 
 int /*<<< orphan*/  OSAddAtomic (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OSAddAtomic64 (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PACK_C_SIZE (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PAGE_REPLACEMENT_DISALLOWED (scalar_t__) ; 
 int PAGE_SIZE ; 
 scalar_t__ TRUE ; 
 size_t UNPACK_C_SIZE (TYPE_2__*) ; 
 scalar_t__ VM_COMPRESSOR_DEFAULT_CODEC ; 
 int /*<<< orphan*/  VM_SWAP_FLAGS_NONE ; 
 int /*<<< orphan*/  WKdm_decompress_new (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 scalar_t__ __improbable (scalar_t__) ; 
 scalar_t__ __probable (int) ; 
 int /*<<< orphan*/ * age_of_decompressions_during_sample_period ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  c_master_lock ; 
 int /*<<< orphan*/  c_seg_move_to_sparse_list (TYPE_4__*) ; 
 int /*<<< orphan*/  c_seg_need_delayed_compaction (TYPE_4__*,scalar_t__) ; 
 int c_seg_swapin (TYPE_4__*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  c_seg_try_minor_compaction_and_unlock (TYPE_4__*) ; 
 int /*<<< orphan*/  c_seg_wait_on_busy (TYPE_4__*) ; 
 int /*<<< orphan*/  c_segment_pages_compressed ; 
 TYPE_5__* c_segments ; 
 size_t c_segments_available ; 
 int /*<<< orphan*/  clock_get_system_nanotime (scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  compressor_bytes_used ; 
 size_t compressor_cpus ; 
 int /*<<< orphan*/  compressor_map ; 
 char* compressor_scratch_bufs ; 
 size_t cpu_number () ; 
 char* kdp_compressor_scratch_buf ; 
 scalar_t__ kdp_lck_mtx_lock_spin_is_acquired (int /*<<< orphan*/ *) ; 
 scalar_t__ kdp_lck_rw_lock_is_acquired_exclusive (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kernel_memory_depopulate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_lock_spin_always (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_unlock_always (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ not_in_kdp ; 
 int /*<<< orphan*/  overage_decompressions_during_sample_period ; 
 int /*<<< orphan*/  panic (char*,...) ; 
 int round_page_32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sample_period_decompression_count ; 
 int /*<<< orphan*/  sv_decompress (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ vm_compressor_algorithm () ; 
 size_t vm_compressor_get_decode_scratch_size () ; 
 int /*<<< orphan*/  vm_swap_consider_defragmenting (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
c_decompress_page(char *dst, volatile c_slot_mapping_t slot_ptr, int flags, int *zeroslot)
{
	c_slot_t	cs;
	c_segment_t	c_seg;
	uint32_t	c_segno;
	int		c_indx;
	int		c_rounded_size;
	uint32_t	c_size;
	int		retval = 0;
	boolean_t	need_unlock = TRUE;
	boolean_t	consider_defragmenting = FALSE;
	boolean_t	kdp_mode = FALSE;

	if (__improbable(flags & C_KDP)) {
		if (not_in_kdp) {
			panic("C_KDP passed to decompress page from outside of debugger context");
		}

		assert((flags & C_KEEP) == C_KEEP);
		assert((flags & C_DONT_BLOCK) == C_DONT_BLOCK);

		if ((flags & (C_DONT_BLOCK | C_KEEP)) != (C_DONT_BLOCK | C_KEEP)) {
			return (-2);
		}

		kdp_mode = TRUE;
		*zeroslot = 0;
	}

ReTry:
	if (__probable(!kdp_mode)) {
		PAGE_REPLACEMENT_DISALLOWED(TRUE);
	} else {
		if (kdp_lck_rw_lock_is_acquired_exclusive(&c_master_lock)) {
			return (-2);
		}
	}

#if HIBERNATION
	/*
	 * if hibernation is enabled, it indicates (via a call
	 * to 'vm_decompressor_lock' that no further
	 * decompressions are allowed once it reaches
	 * the point of flushing all of the currently dirty
	 * anonymous memory through the compressor and out
	 * to disk... in this state we allow freeing of compressed
	 * pages and must honor the C_DONT_BLOCK case
	 */
	if (__improbable(dst && decompressions_blocked == TRUE)) {
		if (flags & C_DONT_BLOCK) {

			if (__probable(!kdp_mode)) {
				PAGE_REPLACEMENT_DISALLOWED(FALSE);
			}

			*zeroslot = 0;
			return (-2);
		}
		/*
		 * it's safe to atomically assert and block behind the
		 * lock held in shared mode because "decompressions_blocked" is
		 * only set and cleared and the thread_wakeup done when the lock
		 * is held exclusively
		 */
		assert_wait((event_t)&decompressions_blocked, THREAD_UNINT);

		PAGE_REPLACEMENT_DISALLOWED(FALSE);

		thread_block(THREAD_CONTINUE_NULL);

		goto ReTry;
	}
#endif
	/* s_cseg is actually "segno+1" */
	c_segno = slot_ptr->s_cseg - 1;

	if (__improbable(c_segno >= c_segments_available))
		panic("c_decompress_page: c_segno %d >= c_segments_available %d, slot_ptr(%p), slot_data(%x)",
		      c_segno, c_segments_available, slot_ptr, *(int *)((void *)slot_ptr));

	if (__improbable(c_segments[c_segno].c_segno < c_segments_available))
		panic("c_decompress_page: c_segno %d is free, slot_ptr(%p), slot_data(%x)",
		      c_segno, slot_ptr, *(int *)((void *)slot_ptr));

	c_seg = c_segments[c_segno].c_seg;

	if (__probable(!kdp_mode)) {
		lck_mtx_lock_spin_always(&c_seg->c_lock);
	} else {
		if (kdp_lck_mtx_lock_spin_is_acquired(&c_seg->c_lock)) {
			return (-2);
		}
	}

	assert(c_seg->c_state != C_IS_EMPTY && c_seg->c_state != C_IS_FREE);

	if (dst == NULL && c_seg->c_busy_swapping) {
		assert(c_seg->c_busy);

		goto bypass_busy_check;
	}
	if (flags & C_DONT_BLOCK) {
		if (c_seg->c_busy || (C_SEG_IS_ONDISK(c_seg) && dst)) {
			*zeroslot = 0;

			retval = -2;
			goto done;
		}
	}
	if (c_seg->c_busy) {

		PAGE_REPLACEMENT_DISALLOWED(FALSE);

		c_seg_wait_on_busy(c_seg);

		goto ReTry;
	}
bypass_busy_check:

	c_indx = slot_ptr->s_cindx;

	if (__improbable(c_indx >= c_seg->c_nextslot))
		panic("c_decompress_page: c_indx %d >= c_nextslot %d, c_seg(%p), slot_ptr(%p), slot_data(%x)",
		      c_indx, c_seg->c_nextslot, c_seg, slot_ptr, *(int *)((void *)slot_ptr));

	cs = C_SEG_SLOT_FROM_INDEX(c_seg, c_indx);

	c_size = UNPACK_C_SIZE(cs);

	if (__improbable(c_size == 0))
		panic("c_decompress_page: c_size == 0, c_seg(%p), slot_ptr(%p), slot_data(%x)",
		      c_seg, slot_ptr, *(int *)((void *)slot_ptr));

	c_rounded_size = (c_size + C_SEG_OFFSET_ALIGNMENT_MASK) & ~C_SEG_OFFSET_ALIGNMENT_MASK;

	if (dst) {
		uint32_t	age_of_cseg;
		clock_sec_t	cur_ts_sec;
		clock_nsec_t	cur_ts_nsec;

		if (C_SEG_IS_ONDISK(c_seg)) {
			assert(kdp_mode == FALSE);
			retval = c_seg_swapin(c_seg, FALSE, TRUE);
			assert(retval == 0);

			retval = 1;
		}		
		if (c_seg->c_state == C_ON_BAD_Q) {
			assert(c_seg->c_store.c_buffer == NULL);
			*zeroslot = 0;

			retval = -1;
			goto done;
		}

#if POPCOUNT_THE_COMPRESSED_DATA
		unsigned csvpop;
		uintptr_t csvaddr = (uintptr_t) &c_seg->c_store.c_buffer[cs->c_offset];
		if (cs->c_pop_cdata != (csvpop = vmc_pop(csvaddr, c_size))) {
			panic("Compressed data popcount doesn't match original, bit distance: %d %p (phys: %p) %p %p 0x%llx 0x%x 0x%x 0x%x", (csvpop - cs->c_pop_cdata), (void *)csvaddr, (void *) kvtophys(csvaddr), c_seg, cs, cs->c_offset, c_size, csvpop, cs->c_pop_cdata);
		}
#endif

#if CHECKSUM_THE_COMPRESSED_DATA
		unsigned csvhash;
		if (cs->c_hash_compressed_data != (csvhash = vmc_hash((char *)&c_seg->c_store.c_buffer[cs->c_offset], c_size))) {
			panic("Compressed data doesn't match original %p %p %u %u %u", c_seg, cs, c_size, cs->c_hash_compressed_data, csvhash);
		}
#endif
		if (c_rounded_size == PAGE_SIZE) {
			/*
			 * page wasn't compressible... just copy it out
			 */
			memcpy(dst, &c_seg->c_store.c_buffer[cs->c_offset], PAGE_SIZE);
		} else if (c_size == 4) {
			int32_t		data;
			int32_t		*dptr;

			/*
			 * page was populated with a single value
			 * that didn't fit into our fast hash
			 * so we packed it in as a single non-compressed value
			 * that we need to populate the page with
			 */
			dptr = (int32_t *)(uintptr_t)dst;
			data = *(int32_t *)(&c_seg->c_store.c_buffer[cs->c_offset]);
			sv_decompress(dptr, data);
		} else {
			uint32_t	my_cpu_no;
			char		*scratch_buf;

			if (__probable(!kdp_mode)) {
				/*
				 * we're behind the c_seg lock held in spin mode
				 * which means pre-emption is disabled... therefore
				 * the following sequence is atomic and safe
				 */
				my_cpu_no = cpu_number();

				assert(my_cpu_no < compressor_cpus);

				scratch_buf = &compressor_scratch_bufs[my_cpu_no * vm_compressor_get_decode_scratch_size()];
			} else {
				scratch_buf = kdp_compressor_scratch_buf;
			}

			if (vm_compressor_algorithm() != VM_COMPRESSOR_DEFAULT_CODEC) {
#if defined(__arm__) || defined(__arm64__)
				uint16_t c_codec = cs->c_codec;
				metadecompressor((const uint8_t *) &c_seg->c_store.c_buffer[cs->c_offset],
				    (uint8_t *)dst, c_size, c_codec, (void *)scratch_buf);
#endif
			} else {
#if defined(__arm64__)
			__unreachable_ok_push
			if (PAGE_SIZE == 4096)
				WKdm_decompress_4k((WK_word *)(uintptr_t)&c_seg->c_store.c_buffer[cs->c_offset],
						   (WK_word *)(uintptr_t)dst, (WK_word *)(uintptr_t)scratch_buf, c_size);
			else {
				WKdm_decompress_16k((WK_word *)(uintptr_t)&c_seg->c_store.c_buffer[cs->c_offset],
						    (WK_word *)(uintptr_t)dst, (WK_word *)(uintptr_t)scratch_buf, c_size);
			}
			__unreachable_ok_pop
#else
			WKdm_decompress_new((WK_word *)(uintptr_t)&c_seg->c_store.c_buffer[cs->c_offset],
					    (WK_word *)(uintptr_t)dst, (WK_word *)(uintptr_t)scratch_buf, c_size);
#endif
			}
		}

#if CHECKSUM_THE_DATA
		if (cs->c_hash_data != vmc_hash(dst, PAGE_SIZE)) {
#if	defined(__arm__) || defined(__arm64__)
			int32_t *dinput = &c_seg->c_store.c_buffer[cs->c_offset];
			panic("decompressed data doesn't match original cs: %p, hash: 0x%x, offset: %d, c_size: %d, c_rounded_size: %d, codec: %d, header: 0x%x 0x%x 0x%x", cs, cs->c_hash_data, cs->c_offset, c_size, c_rounded_size, cs->c_codec, *dinput, *(dinput + 1), *(dinput + 2));
#else
		panic("decompressed data doesn't match original cs: %p, hash: %d, offset: 0x%x, c_size: %d", cs, cs->c_hash_data, cs->c_offset, c_size);
#endif
		}
#endif
		if (c_seg->c_swappedin_ts == 0 && !kdp_mode) {

			clock_get_system_nanotime(&cur_ts_sec, &cur_ts_nsec);

			age_of_cseg = (uint32_t)cur_ts_sec - c_seg->c_creation_ts;
			if (age_of_cseg < DECOMPRESSION_SAMPLE_MAX_AGE)
				OSAddAtomic(1, &age_of_decompressions_during_sample_period[age_of_cseg]);
			else
				OSAddAtomic(1, &overage_decompressions_during_sample_period);

			OSAddAtomic(1, &sample_period_decompression_count);
		}
	}
	if (flags & C_KEEP) {
		*zeroslot = 0;
		goto done;
	}
	assert(kdp_mode == FALSE);

	c_seg->c_bytes_unused += c_rounded_size;
	c_seg->c_bytes_used -= c_rounded_size;

	assert(c_seg->c_slots_used);
	c_seg->c_slots_used--;

	PACK_C_SIZE(cs, 0);

	if (c_indx < c_seg->c_firstemptyslot)
		c_seg->c_firstemptyslot = c_indx;

	OSAddAtomic(-1, &c_segment_pages_compressed);

	if (c_seg->c_state != C_ON_BAD_Q && !(C_SEG_IS_ONDISK(c_seg))) {
		/*
		 * C_SEG_IS_ONDISK == TRUE can occur when we're doing a
		 * free of a compressed page (i.e. dst == NULL)
		 */
		OSAddAtomic64(-c_rounded_size, &compressor_bytes_used);
	}
	if (c_seg->c_busy_swapping) {
		/*
		 * bypass case for c_busy_swapping...
		 * let the swapin/swapout paths deal with putting
		 * the c_seg on the minor compaction queue if needed
		 */
		assert(c_seg->c_busy);
		goto done;
	}
	assert(!c_seg->c_busy);

	if (c_seg->c_state != C_IS_FILLING) {
		if (c_seg->c_bytes_used == 0) {
			if ( !(C_SEG_IS_ONDISK(c_seg))) {
				int	pages_populated;

				pages_populated = (round_page_32(C_SEG_OFFSET_TO_BYTES(c_seg->c_populated_offset))) / PAGE_SIZE;
				c_seg->c_populated_offset = C_SEG_BYTES_TO_OFFSET(0);

				if (pages_populated) {

					assert(c_seg->c_state != C_ON_BAD_Q);
					assert(c_seg->c_store.c_buffer != NULL);

					C_SEG_BUSY(c_seg);
					lck_mtx_unlock_always(&c_seg->c_lock);

					kernel_memory_depopulate(compressor_map, (vm_offset_t) c_seg->c_store.c_buffer, pages_populated * PAGE_SIZE, KMA_COMPRESSOR);

					lck_mtx_lock_spin_always(&c_seg->c_lock);
					C_SEG_WAKEUP_DONE(c_seg);
				}
				if (!c_seg->c_on_minorcompact_q && c_seg->c_state != C_ON_SWAPOUT_Q && c_seg->c_state != C_ON_SWAPIO_Q)
					c_seg_need_delayed_compaction(c_seg, FALSE);
			} else {
				if (c_seg->c_state != C_ON_SWAPPEDOUTSPARSE_Q) {

					c_seg_move_to_sparse_list(c_seg);
					consider_defragmenting = TRUE;
				}
			}
		} else if (c_seg->c_on_minorcompact_q) {

			assert(c_seg->c_state != C_ON_BAD_Q);
			assert(!C_SEG_IS_ON_DISK_OR_SOQ(c_seg));

			if (C_SEG_SHOULD_MINORCOMPACT_NOW(c_seg)) {
				c_seg_try_minor_compaction_and_unlock(c_seg);
				need_unlock = FALSE;
			}
		} else if ( !(C_SEG_IS_ONDISK(c_seg))) {

			if (c_seg->c_state != C_ON_BAD_Q && c_seg->c_state != C_ON_SWAPOUT_Q && c_seg->c_state != C_ON_SWAPIO_Q &&
			    C_SEG_UNUSED_BYTES(c_seg) >= PAGE_SIZE) {
				c_seg_need_delayed_compaction(c_seg, FALSE);
			}
		} else if (c_seg->c_state != C_ON_SWAPPEDOUTSPARSE_Q && C_SEG_ONDISK_IS_SPARSE(c_seg)) {

			c_seg_move_to_sparse_list(c_seg);
			consider_defragmenting = TRUE;
		}
	}
done:
	if (__improbable(kdp_mode)) {
		return retval;
	}

	if (need_unlock == TRUE)
		lck_mtx_unlock_always(&c_seg->c_lock);

	PAGE_REPLACEMENT_DISALLOWED(FALSE);

	if (consider_defragmenting == TRUE)
		vm_swap_consider_defragmenting(VM_SWAP_FLAGS_NONE);

#if CONFIG_EMBEDDED
	if ((c_minor_count && COMPRESSOR_NEEDS_TO_MINOR_COMPACT()) || vm_compressor_needs_to_major_compact())
		vm_wake_compactor_swapper();
#endif

	return (retval);
}