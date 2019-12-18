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
struct journal_head {int /*<<< orphan*/  b_committed_data; } ;
struct buffer_head {int /*<<< orphan*/  b_data; } ;
typedef  int /*<<< orphan*/  ext3_grpblk_t ;

/* Variables and functions */
 struct journal_head* bh2jh (struct buffer_head*) ; 
 scalar_t__ ext3_test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jbd_lock_bh_state (struct buffer_head*) ; 
 int /*<<< orphan*/  jbd_unlock_bh_state (struct buffer_head*) ; 

__attribute__((used)) static int ext3_test_allocatable(ext3_grpblk_t nr, struct buffer_head *bh)
{
	int ret;
	struct journal_head *jh = bh2jh(bh);

	if (ext3_test_bit(nr, bh->b_data))
		return 0;

	jbd_lock_bh_state(bh);
	if (!jh->b_committed_data)
		ret = 1;
	else
		ret = !ext3_test_bit(nr, jh->b_committed_data);
	jbd_unlock_bh_state(bh);
	return ret;
}