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

/* Variables and functions */
 int /*<<< orphan*/  affs_commit_super (struct super_block*,int) ; 
 int /*<<< orphan*/  lock_super (struct super_block*) ; 
 int /*<<< orphan*/  unlock_super (struct super_block*) ; 

__attribute__((used)) static int
affs_sync_fs(struct super_block *sb, int wait)
{
	lock_super(sb);
	affs_commit_super(sb, 2);
	sb->s_dirt = 0;
	unlock_super(sb);
	return 0;
}