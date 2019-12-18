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
struct task_struct {struct fs_struct* fs; } ;
struct path {int dummy; } ;
struct fs_struct {int /*<<< orphan*/  lock; struct path pwd; struct path root; } ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  path_get (struct path*) ; 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  task_lock (struct task_struct*) ; 
 int /*<<< orphan*/  task_unlock (struct task_struct*) ; 

__attribute__((used)) static int get_fs_path(struct task_struct *task, struct path *path, bool root)
{
	struct fs_struct *fs;
	int result = -ENOENT;

	task_lock(task);
	fs = task->fs;
	if (fs) {
		read_lock(&fs->lock);
		*path = root ? fs->root : fs->pwd;
		path_get(path);
		read_unlock(&fs->lock);
		result = 0;
	}
	task_unlock(task);
	return result;
}