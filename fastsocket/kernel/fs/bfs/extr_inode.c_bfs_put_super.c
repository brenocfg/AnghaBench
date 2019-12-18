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
struct super_block {int /*<<< orphan*/ * s_fs_info; scalar_t__ s_dirt; } ;
struct bfs_sb_info {struct bfs_sb_info* si_imap; int /*<<< orphan*/  bfs_lock; int /*<<< orphan*/  si_sbh; } ;

/* Variables and functions */
 struct bfs_sb_info* BFS_SB (struct super_block*) ; 
 int /*<<< orphan*/  bfs_write_super (struct super_block*) ; 
 int /*<<< orphan*/  brelse (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct bfs_sb_info*) ; 
 int /*<<< orphan*/  lock_kernel () ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unlock_kernel () ; 

__attribute__((used)) static void bfs_put_super(struct super_block *s)
{
	struct bfs_sb_info *info = BFS_SB(s);

	if (!info)
		return;

	lock_kernel();

	if (s->s_dirt)
		bfs_write_super(s);

	brelse(info->si_sbh);
	mutex_destroy(&info->bfs_lock);
	kfree(info->si_imap);
	kfree(info);
	s->s_fs_info = NULL;

	unlock_kernel();
}