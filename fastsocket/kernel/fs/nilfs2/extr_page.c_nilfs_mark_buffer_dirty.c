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
struct buffer_head {int /*<<< orphan*/  b_page; } ;

/* Variables and functions */
 int /*<<< orphan*/  __set_page_dirty_nobuffers (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  buffer_dirty (struct buffer_head*) ; 
 int /*<<< orphan*/  test_set_buffer_dirty (struct buffer_head*) ; 

void nilfs_mark_buffer_dirty(struct buffer_head *bh)
{
	if (!buffer_dirty(bh) && !test_set_buffer_dirty(bh))
		__set_page_dirty_nobuffers(bh->b_page);
}