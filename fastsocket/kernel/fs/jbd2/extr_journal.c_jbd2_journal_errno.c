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
struct TYPE_3__ {int j_flags; int j_errno; int /*<<< orphan*/  j_state_lock; } ;
typedef  TYPE_1__ journal_t ;

/* Variables and functions */
 int EROFS ; 
 int JBD2_ABORT ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int jbd2_journal_errno(journal_t *journal)
{
	int err;

	spin_lock(&journal->j_state_lock);
	if (journal->j_flags & JBD2_ABORT)
		err = -EROFS;
	else
		err = journal->j_errno;
	spin_unlock(&journal->j_state_lock);
	return err;
}