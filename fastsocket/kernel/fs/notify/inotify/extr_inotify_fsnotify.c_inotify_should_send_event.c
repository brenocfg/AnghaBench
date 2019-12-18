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
struct inode {int /*<<< orphan*/  i_lock; } ;
struct fsnotify_mark_entry {int mask; } ;
struct fsnotify_group {int dummy; } ;
typedef  int __u32 ;

/* Variables and functions */
 int FS_EVENT_ON_CHILD ; 
 struct fsnotify_mark_entry* fsnotify_find_mark_entry (struct fsnotify_group*,struct inode*) ; 
 int /*<<< orphan*/  fsnotify_put_mark (struct fsnotify_mark_entry*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool inotify_should_send_event(struct fsnotify_group *group, struct inode *inode, __u32 mask)
{
	struct fsnotify_mark_entry *entry;
	bool send;

	spin_lock(&inode->i_lock);
	entry = fsnotify_find_mark_entry(group, inode);
	spin_unlock(&inode->i_lock);
	if (!entry)
		return false;

	mask = (mask & ~FS_EVENT_ON_CHILD);
	send = (entry->mask & mask);

	/* find took a reference */
	fsnotify_put_mark(entry);

	return send;
}