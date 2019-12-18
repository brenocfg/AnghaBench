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
struct path {scalar_t__ dentry; } ;
struct fs_struct {int /*<<< orphan*/  lock; struct path root; } ;

/* Variables and functions */
 int /*<<< orphan*/  path_get (struct path*) ; 
 int /*<<< orphan*/  path_put (struct path*) ; 
 int /*<<< orphan*/  write_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock (int /*<<< orphan*/ *) ; 

void set_fs_root(struct fs_struct *fs, struct path *path)
{
	struct path old_root;

	write_lock(&fs->lock);
	old_root = fs->root;
	fs->root = *path;
	path_get(path);
	write_unlock(&fs->lock);
	if (old_root.dentry)
		path_put(&old_root);
}