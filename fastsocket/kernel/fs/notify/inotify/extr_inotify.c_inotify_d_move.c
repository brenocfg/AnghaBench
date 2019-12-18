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
struct dentry {int /*<<< orphan*/  d_flags; int /*<<< orphan*/  d_inode; struct dentry* d_parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  DCACHE_INOTIFY_PARENT_WATCHED ; 
 scalar_t__ inotify_inode_watched (int /*<<< orphan*/ ) ; 

void inotify_d_move(struct dentry *entry)
{
	struct dentry *parent;

	parent = entry->d_parent;
	if (inotify_inode_watched(parent->d_inode))
		entry->d_flags |= DCACHE_INOTIFY_PARENT_WATCHED;
	else
		entry->d_flags &= ~DCACHE_INOTIFY_PARENT_WATCHED;
}