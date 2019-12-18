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
struct super_block {int s_dirt; } ;
struct ext2_sb_info {int /*<<< orphan*/  s_freeblocks_counter; } ;

/* Variables and functions */
 struct ext2_sb_info* EXT2_SB (struct super_block*) ; 
 int /*<<< orphan*/  percpu_counter_add (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void release_blocks(struct super_block *sb, int count)
{
	if (count) {
		struct ext2_sb_info *sbi = EXT2_SB(sb);

		percpu_counter_add(&sbi->s_freeblocks_counter, count);
		sb->s_dirt = 1;
	}
}