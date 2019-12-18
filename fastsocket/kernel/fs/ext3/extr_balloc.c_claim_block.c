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
struct journal_head {scalar_t__ b_committed_data; } ;
struct buffer_head {int /*<<< orphan*/  b_data; } ;
typedef  int /*<<< orphan*/  spinlock_t ;
typedef  int /*<<< orphan*/  ext3_grpblk_t ;

/* Variables and functions */
 struct journal_head* bh2jh (struct buffer_head*) ; 
 int /*<<< orphan*/  ext3_clear_bit_atomic (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ext3_set_bit_atomic (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ext3_test_bit (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  jbd_lock_bh_state (struct buffer_head*) ; 
 int /*<<< orphan*/  jbd_unlock_bh_state (struct buffer_head*) ; 

__attribute__((used)) static inline int
claim_block(spinlock_t *lock, ext3_grpblk_t block, struct buffer_head *bh)
{
	struct journal_head *jh = bh2jh(bh);
	int ret;

	if (ext3_set_bit_atomic(lock, block, bh->b_data))
		return 0;
	jbd_lock_bh_state(bh);
	if (jh->b_committed_data && ext3_test_bit(block,jh->b_committed_data)) {
		ext3_clear_bit_atomic(lock, block, bh->b_data);
		ret = 0;
	} else {
		ret = 1;
	}
	jbd_unlock_bh_state(bh);
	return ret;
}