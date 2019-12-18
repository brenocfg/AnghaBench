#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct dentry {TYPE_1__* d_inode; } ;
struct TYPE_5__ {struct dentry* dentry; int /*<<< orphan*/  list; } ;
struct TYPE_4__ {int /*<<< orphan*/  i_nlink; } ;
typedef  TYPE_2__ Node ;

/* Variables and functions */
 int /*<<< orphan*/  bm_mnt ; 
 int /*<<< orphan*/  d_drop (struct dentry*) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 int /*<<< orphan*/  entries_lock ; 
 int /*<<< orphan*/  entry_count ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  simple_release_fs (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void kill_node(Node *e)
{
	struct dentry *dentry;

	write_lock(&entries_lock);
	dentry = e->dentry;
	if (dentry) {
		list_del_init(&e->list);
		e->dentry = NULL;
	}
	write_unlock(&entries_lock);

	if (dentry) {
		dentry->d_inode->i_nlink--;
		d_drop(dentry);
		dput(dentry);
		simple_release_fs(&bm_mnt, &entry_count);
	}
}