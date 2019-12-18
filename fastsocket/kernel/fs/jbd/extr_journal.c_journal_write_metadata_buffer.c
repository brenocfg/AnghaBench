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
struct TYPE_6__ {TYPE_2__* t_journal; } ;
typedef  TYPE_1__ transaction_t ;
struct page {int dummy; } ;
struct journal_head {char* b_frozen_data; int /*<<< orphan*/ * b_transaction; } ;
struct buffer_head {char* b_data; unsigned int b_blocknr; int /*<<< orphan*/  b_bdev; int /*<<< orphan*/  b_size; struct page* b_page; int /*<<< orphan*/  b_count; scalar_t__ b_state; } ;
struct TYPE_7__ {int /*<<< orphan*/  j_list_lock; int /*<<< orphan*/  j_dev; } ;
typedef  TYPE_2__ journal_t ;
typedef  scalar_t__ __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  BJ_IO ; 
 int /*<<< orphan*/  BJ_Shadow ; 
 int GFP_NOFS ; 
 int /*<<< orphan*/  JBUFFER_TRACE (struct journal_head*,char*) ; 
 int /*<<< orphan*/  JFS_MAGIC_NUMBER ; 
 int /*<<< orphan*/  J_ASSERT_BH (struct buffer_head*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KM_USER0 ; 
 int __GFP_NOFAIL ; 
 int /*<<< orphan*/  __journal_file_buffer (struct journal_head*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 struct buffer_head* alloc_buffer_head (int) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  buffer_jbddirty (struct buffer_head*) ; 
 scalar_t__ cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_buffer (struct buffer_head*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* jbd_alloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  jbd_free (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jbd_lock_bh_state (struct buffer_head*) ; 
 int /*<<< orphan*/  jbd_unlock_bh_state (struct buffer_head*) ; 
 struct buffer_head* jh2bh (struct journal_head*) ; 
 struct journal_head* journal_add_journal_head (struct buffer_head*) ; 
 int /*<<< orphan*/  journal_file_buffer (struct journal_head*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 char* kmap_atomic (struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kunmap_atomic (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int /*<<< orphan*/ ) ; 
 unsigned int offset_in_page (char*) ; 
 int /*<<< orphan*/  set_bh_page (struct buffer_head*,struct page*,unsigned int) ; 
 int /*<<< orphan*/  set_buffer_dirty (struct buffer_head*) ; 
 int /*<<< orphan*/  set_buffer_mapped (struct buffer_head*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 struct page* virt_to_page (char*) ; 

int journal_write_metadata_buffer(transaction_t *transaction,
				  struct journal_head  *jh_in,
				  struct journal_head **jh_out,
				  unsigned int blocknr)
{
	int need_copy_out = 0;
	int done_copy_out = 0;
	int do_escape = 0;
	char *mapped_data;
	struct buffer_head *new_bh;
	struct journal_head *new_jh;
	struct page *new_page;
	unsigned int new_offset;
	struct buffer_head *bh_in = jh2bh(jh_in);
	journal_t *journal = transaction->t_journal;

	/*
	 * The buffer really shouldn't be locked: only the current committing
	 * transaction is allowed to write it, so nobody else is allowed
	 * to do any IO.
	 *
	 * akpm: except if we're journalling data, and write() output is
	 * also part of a shared mapping, and another thread has
	 * decided to launch a writepage() against this buffer.
	 */
	J_ASSERT_BH(bh_in, buffer_jbddirty(bh_in));

	new_bh = alloc_buffer_head(GFP_NOFS|__GFP_NOFAIL);
	/* keep subsequent assertions sane */
	new_bh->b_state = 0;
	init_buffer(new_bh, NULL, NULL);
	atomic_set(&new_bh->b_count, 1);
	new_jh = journal_add_journal_head(new_bh);	/* This sleeps */

	/*
	 * If a new transaction has already done a buffer copy-out, then
	 * we use that version of the data for the commit.
	 */
	jbd_lock_bh_state(bh_in);
repeat:
	if (jh_in->b_frozen_data) {
		done_copy_out = 1;
		new_page = virt_to_page(jh_in->b_frozen_data);
		new_offset = offset_in_page(jh_in->b_frozen_data);
	} else {
		new_page = jh2bh(jh_in)->b_page;
		new_offset = offset_in_page(jh2bh(jh_in)->b_data);
	}

	mapped_data = kmap_atomic(new_page, KM_USER0);
	/*
	 * Check for escaping
	 */
	if (*((__be32 *)(mapped_data + new_offset)) ==
				cpu_to_be32(JFS_MAGIC_NUMBER)) {
		need_copy_out = 1;
		do_escape = 1;
	}
	kunmap_atomic(mapped_data, KM_USER0);

	/*
	 * Do we need to do a data copy?
	 */
	if (need_copy_out && !done_copy_out) {
		char *tmp;

		jbd_unlock_bh_state(bh_in);
		tmp = jbd_alloc(bh_in->b_size, GFP_NOFS);
		jbd_lock_bh_state(bh_in);
		if (jh_in->b_frozen_data) {
			jbd_free(tmp, bh_in->b_size);
			goto repeat;
		}

		jh_in->b_frozen_data = tmp;
		mapped_data = kmap_atomic(new_page, KM_USER0);
		memcpy(tmp, mapped_data + new_offset, jh2bh(jh_in)->b_size);
		kunmap_atomic(mapped_data, KM_USER0);

		new_page = virt_to_page(tmp);
		new_offset = offset_in_page(tmp);
		done_copy_out = 1;
	}

	/*
	 * Did we need to do an escaping?  Now we've done all the
	 * copying, we can finally do so.
	 */
	if (do_escape) {
		mapped_data = kmap_atomic(new_page, KM_USER0);
		*((unsigned int *)(mapped_data + new_offset)) = 0;
		kunmap_atomic(mapped_data, KM_USER0);
	}

	set_bh_page(new_bh, new_page, new_offset);
	new_jh->b_transaction = NULL;
	new_bh->b_size = jh2bh(jh_in)->b_size;
	new_bh->b_bdev = transaction->t_journal->j_dev;
	new_bh->b_blocknr = blocknr;
	set_buffer_mapped(new_bh);
	set_buffer_dirty(new_bh);

	*jh_out = new_jh;

	/*
	 * The to-be-written buffer needs to get moved to the io queue,
	 * and the original buffer whose contents we are shadowing or
	 * copying is moved to the transaction's shadow queue.
	 */
	JBUFFER_TRACE(jh_in, "file as BJ_Shadow");
	spin_lock(&journal->j_list_lock);
	__journal_file_buffer(jh_in, transaction, BJ_Shadow);
	spin_unlock(&journal->j_list_lock);
	jbd_unlock_bh_state(bh_in);

	JBUFFER_TRACE(new_jh, "file as BJ_IO");
	journal_file_buffer(new_jh, transaction, BJ_IO);

	return do_escape | (done_copy_out << 1);
}