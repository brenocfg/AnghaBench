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
struct super_block {scalar_t__ s_dirt; } ;
struct bfs_sb_info {int /*<<< orphan*/  bfs_lock; int /*<<< orphan*/  si_sbh; } ;

/* Variables and functions */
 struct bfs_sb_info* BFS_SB (struct super_block*) ; 
 int /*<<< orphan*/  mark_buffer_dirty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bfs_sync_fs(struct super_block *sb, int wait)
{
	struct bfs_sb_info *info = BFS_SB(sb);

	mutex_lock(&info->bfs_lock);
	mark_buffer_dirty(info->si_sbh);
	sb->s_dirt = 0;
	mutex_unlock(&info->bfs_lock);

	return 0;
}