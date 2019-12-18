#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* t_journal; } ;
typedef  TYPE_2__ transaction_t ;
struct journal_head {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  j_list_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  __journal_file_buffer (struct journal_head*,TYPE_2__*,int) ; 
 int /*<<< orphan*/  jbd_lock_bh_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jbd_unlock_bh_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jh2bh (struct journal_head*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void journal_file_buffer(struct journal_head *jh,
				transaction_t *transaction, int jlist)
{
	jbd_lock_bh_state(jh2bh(jh));
	spin_lock(&transaction->t_journal->j_list_lock);
	__journal_file_buffer(jh, transaction, jlist);
	spin_unlock(&transaction->t_journal->j_list_lock);
	jbd_unlock_bh_state(jh2bh(jh));
}