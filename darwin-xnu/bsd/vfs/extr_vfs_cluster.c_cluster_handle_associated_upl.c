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
typedef  int /*<<< orphan*/  upl_t ;
typedef  int upl_size_t ;
typedef  int /*<<< orphan*/  upl_page_info_t ;
typedef  int upl_offset_t ;
struct clios {int /*<<< orphan*/  io_mtxp; } ;
typedef  int /*<<< orphan*/  kern_return_t ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 int PAGE_MASK ; 
 int PAGE_SHIFT ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  UPL_ABORT_DUMP_PAGES ; 
 int /*<<< orphan*/ * UPL_GET_INTERNAL_PAGE_LIST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  lck_mtx_lock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,int,int) ; 
 int trunc_page_32 (int) ; 
 int /*<<< orphan*/  upl_abort_range (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  upl_associated_upl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  upl_deallocate (int /*<<< orphan*/ ) ; 
 int upl_get_size (int /*<<< orphan*/ ) ; 
 int upl_page_get_mark (int /*<<< orphan*/ *,int const) ; 
 int /*<<< orphan*/  upl_page_set_mark (int /*<<< orphan*/ *,int const,int) ; 
 int /*<<< orphan*/  upl_set_associated_upl (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cluster_handle_associated_upl(struct clios *iostate, upl_t upl,
										  upl_offset_t upl_offset, upl_size_t size)
{
	if (!size)
		return;

	upl_t associated_upl = upl_associated_upl(upl);

	if (!associated_upl)
		return;

#if 0
	printf("1: %d %d\n", upl_offset, upl_offset + size);
#endif

	/*
	 * The associated UPL is page aligned to file offsets whereas the
	 * UPL it's attached to has different alignment requirements.  The
	 * upl_offset that we have refers to @upl.  The code that follows
	 * has to deal with the first and last pages in this transaction
	 * which might straddle pages in the associated UPL.  To keep
	 * track of these pages, we use the mark bits: if the mark bit is
	 * set, we know another transaction has completed its part of that
	 * page and so we can unlock that page here.
	 *
	 * The following illustrates what we have to deal with:
	 *
	 *    MEM u <------------ 1 PAGE ------------> e
	 *        +-------------+----------------------+-----------------
	 *        |             |######################|#################
	 *        +-------------+----------------------+-----------------
	 *   FILE | <--- a ---> o <------------ 1 PAGE ------------>
	 *
	 * So here we show a write to offset @o.  The data that is to be
	 * written is in a buffer that is not page aligned; it has offset
	 * @a in the page.  The upl that carries the data starts in memory
	 * at @u.  The associated upl starts in the file at offset @o.  A
	 * transaction will always end on a page boundary (like @e above)
	 * except for the very last transaction in the group.  We cannot
	 * unlock the page at @o in the associated upl until both the
	 * transaction ending at @e and the following transaction (that
	 * starts at @e) has completed.
	 */

	/*
	 * We record whether or not the two UPLs are aligned as the mark
	 * bit in the first page of @upl.
	 */
	upl_page_info_t *pl = UPL_GET_INTERNAL_PAGE_LIST(upl);
	bool is_unaligned = upl_page_get_mark(pl, 0);

	if (is_unaligned) {
		upl_page_info_t *assoc_pl = UPL_GET_INTERNAL_PAGE_LIST(associated_upl);

		upl_offset_t upl_end = upl_offset + size;
		assert(upl_end >= PAGE_SIZE);

		upl_size_t assoc_upl_size = upl_get_size(associated_upl);

		/*
		 * In the very first transaction in the group, upl_offset will
		 * not be page aligned, but after that it will be and in that
		 * case we want the preceding page in the associated UPL hence
		 * the minus one.
		 */
		assert(upl_offset);
		if (upl_offset)
			upl_offset = trunc_page_32(upl_offset - 1);

		lck_mtx_lock_spin(&iostate->io_mtxp);

		// Look at the first page...
		if (upl_offset
			&& !upl_page_get_mark(assoc_pl, upl_offset >> PAGE_SHIFT)) {
			/*
			 * The first page isn't marked so let another transaction
			 * completion handle it.
			 */
			upl_page_set_mark(assoc_pl, upl_offset >> PAGE_SHIFT, true);
			upl_offset += PAGE_SIZE;
		}

		// And now the last page...

		/*
		 * This needs to be > rather than >= because if it's equal, it
		 * means there's another transaction that is sharing the last
		 * page.
		 */
		if (upl_end > assoc_upl_size)
			upl_end = assoc_upl_size;
		else {
			upl_end = trunc_page_32(upl_end);
			const int last_pg = (upl_end >> PAGE_SHIFT) - 1;

			if (!upl_page_get_mark(assoc_pl, last_pg)) {
				/*
				 * The last page isn't marked so mark the page and let another
				 * transaction completion handle it.
				 */
				upl_page_set_mark(assoc_pl, last_pg, true);
				upl_end -= PAGE_SIZE;
			}
		}

		lck_mtx_unlock(&iostate->io_mtxp);

#if 0
		printf("2: %d %d\n", upl_offset, upl_end);
#endif

		if (upl_end <= upl_offset)
			return;

		size = upl_end - upl_offset;
	} else {
		assert(!(upl_offset & PAGE_MASK));
		assert(!(size & PAGE_MASK));
	}

	boolean_t empty;

	/*
	 * We can unlock these pages now and as this is for a
	 * direct/uncached write, we want to dump the pages too.
	 */
	kern_return_t kr = upl_abort_range(associated_upl, upl_offset, size,
									   UPL_ABORT_DUMP_PAGES, &empty);

	assert(!kr);

	if (!kr && empty) {
		upl_set_associated_upl(upl, NULL);
		upl_deallocate(associated_upl);
	}
}