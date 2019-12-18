#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {struct journal_head* t_reserved_list; struct journal_head* t_log_list; struct journal_head* t_shadow_list; struct journal_head* t_iobuf_list; struct journal_head* t_forget; struct journal_head* t_buffers; int /*<<< orphan*/  t_nr_buffers; TYPE_1__* t_journal; } ;
typedef  TYPE_2__ transaction_t ;
struct journal_head {int b_jlist; int /*<<< orphan*/  b_frozen_data; int /*<<< orphan*/  b_committed_data; TYPE_2__* b_transaction; } ;
struct buffer_head {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  j_list_lock; } ;

/* Variables and functions */
#define  BJ_Forget 134 
#define  BJ_IO 133 
#define  BJ_LogCtl 132 
#define  BJ_Metadata 131 
#define  BJ_None 130 
#define  BJ_Reserved 129 
#define  BJ_Shadow 128 
 int BJ_Types ; 
 int /*<<< orphan*/  J_ASSERT_JH (struct journal_head*,int) ; 
 int /*<<< orphan*/  __blist_add_buffer (struct journal_head**,struct journal_head*) ; 
 int /*<<< orphan*/  __jbd2_journal_temp_unlink_buffer (struct journal_head*) ; 
 int /*<<< orphan*/  assert_spin_locked (int /*<<< orphan*/ *) ; 
 scalar_t__ buffer_dirty (struct buffer_head*) ; 
 int jbd_is_locked_bh_state (struct buffer_head*) ; 
 struct buffer_head* jh2bh (struct journal_head*) ; 
 int /*<<< orphan*/  set_buffer_jbddirty (struct buffer_head*) ; 
 scalar_t__ test_clear_buffer_dirty (struct buffer_head*) ; 
 scalar_t__ test_clear_buffer_jbddirty (struct buffer_head*) ; 
 int /*<<< orphan*/  warn_dirty_buffer (struct buffer_head*) ; 

void __jbd2_journal_file_buffer(struct journal_head *jh,
			transaction_t *transaction, int jlist)
{
	struct journal_head **list = NULL;
	int was_dirty = 0;
	struct buffer_head *bh = jh2bh(jh);

	J_ASSERT_JH(jh, jbd_is_locked_bh_state(bh));
	assert_spin_locked(&transaction->t_journal->j_list_lock);

	J_ASSERT_JH(jh, jh->b_jlist < BJ_Types);
	J_ASSERT_JH(jh, jh->b_transaction == transaction ||
				jh->b_transaction == NULL);

	if (jh->b_transaction && jh->b_jlist == jlist)
		return;

	if (jlist == BJ_Metadata || jlist == BJ_Reserved ||
	    jlist == BJ_Shadow || jlist == BJ_Forget) {
		/*
		 * For metadata buffers, we track dirty bit in buffer_jbddirty
		 * instead of buffer_dirty. We should not see a dirty bit set
		 * here because we clear it in do_get_write_access but e.g.
		 * tune2fs can modify the sb and set the dirty bit at any time
		 * so we try to gracefully handle that.
		 */
		if (buffer_dirty(bh))
			warn_dirty_buffer(bh);
		if (test_clear_buffer_dirty(bh) ||
		    test_clear_buffer_jbddirty(bh))
			was_dirty = 1;
	}

	if (jh->b_transaction)
		__jbd2_journal_temp_unlink_buffer(jh);
	jh->b_transaction = transaction;

	switch (jlist) {
	case BJ_None:
		J_ASSERT_JH(jh, !jh->b_committed_data);
		J_ASSERT_JH(jh, !jh->b_frozen_data);
		return;
	case BJ_Metadata:
		transaction->t_nr_buffers++;
		list = &transaction->t_buffers;
		break;
	case BJ_Forget:
		list = &transaction->t_forget;
		break;
	case BJ_IO:
		list = &transaction->t_iobuf_list;
		break;
	case BJ_Shadow:
		list = &transaction->t_shadow_list;
		break;
	case BJ_LogCtl:
		list = &transaction->t_log_list;
		break;
	case BJ_Reserved:
		list = &transaction->t_reserved_list;
		break;
	}

	__blist_add_buffer(list, jh);
	jh->b_jlist = jlist;

	if (was_dirty)
		set_buffer_jbddirty(bh);
}