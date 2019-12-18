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
struct super_block {int dummy; } ;
struct buffer_head {int dummy; } ;

/* Variables and functions */
 scalar_t__ buffer_eopnotsupp (struct buffer_head*) ; 
 int /*<<< orphan*/  clear_buffer_eopnotsupp (struct buffer_head*) ; 
 int /*<<< orphan*/  disable_barrier (struct super_block*) ; 
 int /*<<< orphan*/  set_buffer_dirty (struct buffer_head*) ; 
 int /*<<< orphan*/  set_buffer_uptodate (struct buffer_head*) ; 
 int /*<<< orphan*/  sync_dirty_buffer (struct buffer_head*) ; 

__attribute__((used)) static void check_barrier_completion(struct super_block *s,
				     struct buffer_head *bh)
{
	if (buffer_eopnotsupp(bh)) {
		clear_buffer_eopnotsupp(bh);
		disable_barrier(s);
		set_buffer_uptodate(bh);
		set_buffer_dirty(bh);
		sync_dirty_buffer(bh);
	}
}