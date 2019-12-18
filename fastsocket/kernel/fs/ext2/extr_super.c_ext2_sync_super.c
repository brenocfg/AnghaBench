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
struct super_block {scalar_t__ s_dirt; } ;
struct ext2_super_block {void* s_wtime; void* s_free_inodes_count; void* s_free_blocks_count; } ;
struct TYPE_2__ {int /*<<< orphan*/  s_sbh; } ;

/* Variables and functions */
 TYPE_1__* EXT2_SB (struct super_block*) ; 
 void* cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext2_clear_super_error (struct super_block*) ; 
 int /*<<< orphan*/  ext2_count_free_blocks (struct super_block*) ; 
 int /*<<< orphan*/  ext2_count_free_inodes (struct super_block*) ; 
 int /*<<< orphan*/  get_seconds () ; 
 int /*<<< orphan*/  mark_buffer_dirty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sync_dirty_buffer (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ext2_sync_super(struct super_block *sb, struct ext2_super_block *es)
{
	ext2_clear_super_error(sb);
	es->s_free_blocks_count = cpu_to_le32(ext2_count_free_blocks(sb));
	es->s_free_inodes_count = cpu_to_le32(ext2_count_free_inodes(sb));
	es->s_wtime = cpu_to_le32(get_seconds());
	mark_buffer_dirty(EXT2_SB(sb)->s_sbh);
	sync_dirty_buffer(EXT2_SB(sb)->s_sbh);
	sb->s_dirt = 0;
}