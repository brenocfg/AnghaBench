#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  int32_t ;
typedef  TYPE_2__* c_slot_t ;
typedef  TYPE_3__* c_slot_mapping_t ;
typedef  TYPE_4__* c_segment_t ;
typedef  scalar_t__ boolean_t ;
typedef  int /*<<< orphan*/  WK_word ;
struct TYPE_17__ {int /*<<< orphan*/ * c_buffer; } ;
struct TYPE_20__ {scalar_t__ c_state; scalar_t__ c_nextslot; size_t c_nextoffset; int c_bytes_used; int /*<<< orphan*/  c_lock; scalar_t__ c_mysegno; int /*<<< orphan*/  c_slots_used; TYPE_1__ c_store; } ;
struct TYPE_19__ {int s_cindx; scalar_t__ s_cseg; } ;
struct TYPE_18__ {size_t c_offset; int /*<<< orphan*/  c_packed_ptr; } ;

/* Variables and functions */
 scalar_t__ C_IS_FILLING ; 
 int C_SEG_BUFSIZE ; 
 size_t C_SEG_BYTES_TO_OFFSET (int) ; 
 int C_SEG_OFFSET_ALIGNMENT_MASK ; 
 int C_SEG_OFFSET_TO_BYTES (int /*<<< orphan*/ ) ; 
 scalar_t__ C_SEG_OFF_LIMIT ; 
 TYPE_2__* C_SEG_SLOT_FROM_INDEX (TYPE_4__*,scalar_t__) ; 
 scalar_t__ C_SLOT_MAX_INDEX ; 
 int /*<<< orphan*/  C_SLOT_PACK_PTR (TYPE_3__*) ; 
 scalar_t__ C_SLOT_UNPACK_PTR (TYPE_2__*) ; 
 scalar_t__ C_SV_CSEG_ID ; 
 int DBG_FUNC_END ; 
 int DBG_FUNC_START ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  KERNEL_DEBUG (int,TYPE_4__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OSAddAtomic (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OSAddAtomic64 (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PACK_C_SIZE (TYPE_2__*,int) ; 
 int /*<<< orphan*/  PAGE_REPLACEMENT_DISALLOWED (scalar_t__) ; 
 int PAGE_SIZE ; 
 scalar_t__ VM_COMPRESSOR_DEFAULT_CODEC ; 
 int WKdm_compress_new (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  assertf (int,char*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  c_current_seg_filled (TYPE_4__*,TYPE_4__**) ; 
 TYPE_4__* c_seg_allocate (TYPE_4__**) ; 
 int /*<<< orphan*/  c_segment_compressed_bytes ; 
 int /*<<< orphan*/  c_segment_input_bytes ; 
 int /*<<< orphan*/  c_segment_noncompressible_pages ; 
 int /*<<< orphan*/  c_segment_pages_compressed ; 
 int c_segment_sv_hash_insert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  c_segment_svp_hash_failed ; 
 int /*<<< orphan*/  c_segment_svp_hash_succeeded ; 
 int /*<<< orphan*/  compressor_bytes_used ; 
 int /*<<< orphan*/  lck_mtx_unlock_always (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  sample_period_compression_count ; 
 scalar_t__ vm_compressor_algorithm () ; 

__attribute__((used)) static int
c_compress_page(char *src, c_slot_mapping_t slot_ptr, c_segment_t *current_chead, char *scratch_buf)
{
	int		c_size;
	int		c_rounded_size = 0;
	int		max_csize;
	c_slot_t	cs;
	c_segment_t	c_seg;

	KERNEL_DEBUG(0xe0400000 | DBG_FUNC_START, *current_chead, 0, 0, 0, 0);
retry:
	if ((c_seg = c_seg_allocate(current_chead)) == NULL) {
		return (1);
	}
	/*
	 * returns with c_seg lock held
	 * and PAGE_REPLACEMENT_DISALLOWED(TRUE)...
	 * c_nextslot has been allocated and
	 * c_store.c_buffer populated
	 */
	assert(c_seg->c_state == C_IS_FILLING);

	cs = C_SEG_SLOT_FROM_INDEX(c_seg, c_seg->c_nextslot);

	cs->c_packed_ptr = C_SLOT_PACK_PTR(slot_ptr);
	assert(slot_ptr == (c_slot_mapping_t)C_SLOT_UNPACK_PTR(cs));

	cs->c_offset = c_seg->c_nextoffset;

	max_csize = C_SEG_BUFSIZE - C_SEG_OFFSET_TO_BYTES((int32_t)cs->c_offset);

	if (max_csize > PAGE_SIZE)
		max_csize = PAGE_SIZE;

#if CHECKSUM_THE_DATA
	cs->c_hash_data = vmc_hash(src, PAGE_SIZE);
#endif
	boolean_t incomp_copy = FALSE;
	int max_csize_adj = (max_csize - 4);

	if (vm_compressor_algorithm() != VM_COMPRESSOR_DEFAULT_CODEC) {
#if defined(__arm__) || defined(__arm64__)
		uint16_t ccodec = CINVALID;

		if (max_csize >= C_SEG_OFFSET_ALIGNMENT_BOUNDARY) {
			c_size = metacompressor((const uint8_t *) src,
			    (uint8_t *) &c_seg->c_store.c_buffer[cs->c_offset],
			    max_csize_adj, &ccodec,
			    scratch_buf, &incomp_copy);
#if C_SEG_OFFSET_ALIGNMENT_BOUNDARY > 4
			if (c_size > max_csize_adj) {
				c_size = -1;
			}
#endif
		} else {
			c_size = -1;
		}
		assert(ccodec == CCWK || ccodec == CCLZ4);
		cs->c_codec = ccodec;
#endif
	} else {
#if defined(__arm__) || defined(__arm64__)
	cs->c_codec = CCWK;
#endif
#if defined(__arm64__)
	__unreachable_ok_push
	if (PAGE_SIZE == 4096)
		c_size = WKdm_compress_4k((WK_word *)(uintptr_t)src, (WK_word *)(uintptr_t)&c_seg->c_store.c_buffer[cs->c_offset],
					   (WK_word *)(uintptr_t)scratch_buf, max_csize_adj);
	else {
		c_size = WKdm_compress_16k((WK_word *)(uintptr_t)src, (WK_word *)(uintptr_t)&c_seg->c_store.c_buffer[cs->c_offset],
					   (WK_word *)(uintptr_t)scratch_buf, max_csize_adj);
	}
	__unreachable_ok_pop
#else
	c_size = WKdm_compress_new((const WK_word *)(uintptr_t)src, (WK_word *)(uintptr_t)&c_seg->c_store.c_buffer[cs->c_offset],
				  (WK_word *)(uintptr_t)scratch_buf, max_csize_adj);
#endif
	}
	assertf(((c_size <= max_csize_adj) && (c_size >= -1)),
	    "c_size invalid (%d, %d), cur compressions: %d", c_size, max_csize_adj, c_segment_pages_compressed);

	if (c_size == -1) {
		if (max_csize < PAGE_SIZE) {
			c_current_seg_filled(c_seg, current_chead);
			assert(*current_chead == NULL);

			lck_mtx_unlock_always(&c_seg->c_lock);
			/* TODO: it may be worth requiring codecs to distinguish
			 * between incompressible inputs and failures due to
			 * budget exhaustion.
			 */
			PAGE_REPLACEMENT_DISALLOWED(FALSE);
			goto retry;
		}
		c_size = PAGE_SIZE;

		if (incomp_copy == FALSE) {
			memcpy(&c_seg->c_store.c_buffer[cs->c_offset], src, c_size);
		}

		OSAddAtomic(1, &c_segment_noncompressible_pages);

	} else if (c_size == 0) {
		int		hash_index;

		/*
		 * special case - this is a page completely full of a single 32 bit value
		 */
		hash_index = c_segment_sv_hash_insert(*(uint32_t *)(uintptr_t)src);

		if (hash_index != -1) {
			slot_ptr->s_cindx = hash_index;
			slot_ptr->s_cseg = C_SV_CSEG_ID;

			OSAddAtomic(1, &c_segment_svp_hash_succeeded);
#if RECORD_THE_COMPRESSED_DATA
			c_compressed_record_data(src, 4);
#endif
			goto sv_compression;
		}
		c_size = 4;
		
		memcpy(&c_seg->c_store.c_buffer[cs->c_offset], src, c_size);

		OSAddAtomic(1, &c_segment_svp_hash_failed);
	}

#if RECORD_THE_COMPRESSED_DATA
	c_compressed_record_data((char *)&c_seg->c_store.c_buffer[cs->c_offset], c_size);
#endif
#if CHECKSUM_THE_COMPRESSED_DATA
	cs->c_hash_compressed_data = vmc_hash((char *)&c_seg->c_store.c_buffer[cs->c_offset], c_size);
#endif
#if POPCOUNT_THE_COMPRESSED_DATA
	cs->c_pop_cdata = vmc_pop((uintptr_t) &c_seg->c_store.c_buffer[cs->c_offset], c_size);
#endif
	c_rounded_size = (c_size + C_SEG_OFFSET_ALIGNMENT_MASK) & ~C_SEG_OFFSET_ALIGNMENT_MASK;

	PACK_C_SIZE(cs, c_size);
	c_seg->c_bytes_used += c_rounded_size;
	c_seg->c_nextoffset += C_SEG_BYTES_TO_OFFSET(c_rounded_size);
	c_seg->c_slots_used++;

	slot_ptr->s_cindx = c_seg->c_nextslot++;
	/* <csegno=0,indx=0> would mean "empty slot", so use csegno+1 */
	slot_ptr->s_cseg = c_seg->c_mysegno + 1; 

sv_compression:
	if (c_seg->c_nextoffset >= C_SEG_OFF_LIMIT || c_seg->c_nextslot >= C_SLOT_MAX_INDEX) {
		c_current_seg_filled(c_seg, current_chead);
		assert(*current_chead == NULL);
	}
	lck_mtx_unlock_always(&c_seg->c_lock);

	PAGE_REPLACEMENT_DISALLOWED(FALSE);

#if RECORD_THE_COMPRESSED_DATA
	if ((c_compressed_record_cptr - c_compressed_record_sbuf) >= C_SEG_ALLOCSIZE) {
		c_compressed_record_write(c_compressed_record_sbuf, (int)(c_compressed_record_cptr - c_compressed_record_sbuf));
		c_compressed_record_cptr = c_compressed_record_sbuf;
	}
#endif
	if (c_size) {
		OSAddAtomic64(c_size, &c_segment_compressed_bytes);
		OSAddAtomic64(c_rounded_size, &compressor_bytes_used);
	}
	OSAddAtomic64(PAGE_SIZE, &c_segment_input_bytes);

	OSAddAtomic(1, &c_segment_pages_compressed);
	OSAddAtomic(1, &sample_period_compression_count);

	KERNEL_DEBUG(0xe0400000 | DBG_FUNC_END, *current_chead, c_size, c_segment_input_bytes, c_segment_compressed_bytes, 0);

	return (0);
}