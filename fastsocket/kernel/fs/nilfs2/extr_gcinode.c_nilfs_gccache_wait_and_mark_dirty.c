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
struct buffer_head {int dummy; } ;

/* Variables and functions */
 int EEXIST ; 
 int EIO ; 
 scalar_t__ buffer_dirty (struct buffer_head*) ; 
 scalar_t__ buffer_nilfs_node (struct buffer_head*) ; 
 int /*<<< orphan*/  buffer_uptodate (struct buffer_head*) ; 
 int /*<<< orphan*/  nilfs_btnode_mark_dirty (struct buffer_head*) ; 
 int /*<<< orphan*/  nilfs_mdt_mark_buffer_dirty (struct buffer_head*) ; 
 int /*<<< orphan*/  wait_on_buffer (struct buffer_head*) ; 

int nilfs_gccache_wait_and_mark_dirty(struct buffer_head *bh)
{
	wait_on_buffer(bh);
	if (!buffer_uptodate(bh))
		return -EIO;
	if (buffer_dirty(bh))
		return -EEXIST;

	if (buffer_nilfs_node(bh))
		nilfs_btnode_mark_dirty(bh);
	else
		nilfs_mdt_mark_buffer_dirty(bh);
	return 0;
}