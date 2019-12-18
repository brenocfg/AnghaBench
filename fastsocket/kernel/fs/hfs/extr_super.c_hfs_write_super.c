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
struct super_block {int s_flags; scalar_t__ s_dirt; } ;

/* Variables and functions */
 int MS_RDONLY ; 
 int /*<<< orphan*/  hfs_mdb_commit (struct super_block*) ; 
 int /*<<< orphan*/  lock_super (struct super_block*) ; 
 int /*<<< orphan*/  unlock_super (struct super_block*) ; 

__attribute__((used)) static void hfs_write_super(struct super_block *sb)
{
	lock_super(sb);
	sb->s_dirt = 0;

	/* sync everything to the buffers */
	if (!(sb->s_flags & MS_RDONLY))
		hfs_mdb_commit(sb);
	unlock_super(sb);
}