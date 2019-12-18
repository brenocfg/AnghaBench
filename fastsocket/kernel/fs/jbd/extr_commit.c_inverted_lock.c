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
struct buffer_head {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  j_list_lock; } ;
typedef  TYPE_1__ journal_t ;

/* Variables and functions */
 int /*<<< orphan*/  jbd_trylock_bh_state (struct buffer_head*) ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int inverted_lock(journal_t *journal, struct buffer_head *bh)
{
	if (!jbd_trylock_bh_state(bh)) {
		spin_unlock(&journal->j_list_lock);
		schedule();
		return 0;
	}
	return 1;
}