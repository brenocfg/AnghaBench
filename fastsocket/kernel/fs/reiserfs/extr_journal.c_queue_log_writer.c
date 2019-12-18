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
typedef  int /*<<< orphan*/  wait_queue_t ;
struct super_block {int dummy; } ;
struct reiserfs_journal {int /*<<< orphan*/  j_join_wait; int /*<<< orphan*/  j_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  J_WRITERS_QUEUED ; 
 struct reiserfs_journal* SB_JOURNAL (struct super_block*) ; 
 int /*<<< orphan*/  TASK_RUNNING ; 
 int /*<<< orphan*/  TASK_UNINTERRUPTIBLE ; 
 int /*<<< orphan*/  __set_current_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  init_waitqueue_entry (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  remove_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void queue_log_writer(struct super_block *s)
{
	wait_queue_t wait;
	struct reiserfs_journal *journal = SB_JOURNAL(s);
	set_bit(J_WRITERS_QUEUED, &journal->j_state);

	/*
	 * we don't want to use wait_event here because
	 * we only want to wait once.
	 */
	init_waitqueue_entry(&wait, current);
	add_wait_queue(&journal->j_join_wait, &wait);
	set_current_state(TASK_UNINTERRUPTIBLE);
	if (test_bit(J_WRITERS_QUEUED, &journal->j_state))
		schedule();
	__set_current_state(TASK_RUNNING);
	remove_wait_queue(&journal->j_join_wait, &wait);
}