#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct super_block {int /*<<< orphan*/  s_blocksize; } ;
struct buffer_head {int /*<<< orphan*/  b_data; } ;
struct TYPE_2__ {int s_reserved; int s_partition_size; } ;

/* Variables and functions */
 TYPE_1__* AFFS_SB (struct super_block*) ; 
 int /*<<< orphan*/  lock_buffer (struct buffer_head*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int) ; 
 struct buffer_head* sb_getblk (struct super_block*,int) ; 
 int /*<<< orphan*/  set_buffer_uptodate (struct buffer_head*) ; 
 int /*<<< orphan*/  unlock_buffer (struct buffer_head*) ; 

__attribute__((used)) static inline struct buffer_head *
affs_getzeroblk(struct super_block *sb, int block)
{
	struct buffer_head *bh;
	pr_debug("affs_getzeroblk: %d\n", block);
	if (block >= AFFS_SB(sb)->s_reserved && block < AFFS_SB(sb)->s_partition_size) {
		bh = sb_getblk(sb, block);
		lock_buffer(bh);
		memset(bh->b_data, 0 , sb->s_blocksize);
		set_buffer_uptodate(bh);
		unlock_buffer(bh);
		return bh;
	}
	return NULL;
}