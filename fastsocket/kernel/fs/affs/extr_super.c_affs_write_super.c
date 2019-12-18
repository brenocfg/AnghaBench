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
struct super_block {int s_flags; int s_dirt; } ;

/* Variables and functions */
 int MS_RDONLY ; 
 int /*<<< orphan*/  affs_commit_super (struct super_block*,int) ; 
 int /*<<< orphan*/  get_seconds () ; 
 int /*<<< orphan*/  lock_super (struct super_block*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  unlock_super (struct super_block*) ; 

__attribute__((used)) static void
affs_write_super(struct super_block *sb)
{
	int clean = 2;

	lock_super(sb);
	if (!(sb->s_flags & MS_RDONLY)) {
		//	if (sbi->s_bitmap[i].bm_bh) {
		//		if (buffer_dirty(sbi->s_bitmap[i].bm_bh)) {
		//			clean = 0;
		affs_commit_super(sb, clean);
		sb->s_dirt = !clean;	/* redo until bitmap synced */
	} else
		sb->s_dirt = 0;
	unlock_super(sb);

	pr_debug("AFFS: write_super() at %lu, clean=%d\n", get_seconds(), clean);
}