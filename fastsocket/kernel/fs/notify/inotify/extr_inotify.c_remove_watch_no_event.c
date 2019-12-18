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
struct inotify_watch {int /*<<< orphan*/  wd; int /*<<< orphan*/  inode; int /*<<< orphan*/  h_list; int /*<<< orphan*/  i_list; } ;
struct inotify_handle {int /*<<< orphan*/  idr; } ;

/* Variables and functions */
 int /*<<< orphan*/  idr_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inotify_inode_watched (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_dentry_child_flags (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void remove_watch_no_event(struct inotify_watch *watch,
				  struct inotify_handle *ih)
{
	list_del(&watch->i_list);
	list_del(&watch->h_list);

	if (!inotify_inode_watched(watch->inode))
		set_dentry_child_flags(watch->inode, 0);

	idr_remove(&ih->idr, watch->wd);
}