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
struct TYPE_3__ {int j_free; int /*<<< orphan*/  j_state_lock; } ;
typedef  TYPE_1__ journal_t ;

/* Variables and functions */
 scalar_t__ MIN_LOG_RESERVED_BLOCKS ; 
 int /*<<< orphan*/  assert_spin_locked (int /*<<< orphan*/ *) ; 

int __jbd2_log_space_left(journal_t *journal)
{
	int left = journal->j_free;

	assert_spin_locked(&journal->j_state_lock);

	/*
	 * Be pessimistic here about the number of those free blocks which
	 * might be required for log descriptor control blocks.
	 */

#define MIN_LOG_RESERVED_BLOCKS 32 /* Allow for rounding errors */

	left -= MIN_LOG_RESERVED_BLOCKS;

	if (left <= 0)
		return 0;
	left -= (left >> 3);
	return left;
}