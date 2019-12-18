#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct fs_struct {int /*<<< orphan*/  lock; int /*<<< orphan*/  users; } ;
struct TYPE_4__ {struct fs_struct* fs; } ;

/* Variables and functions */
 TYPE_1__* current ; 
 int /*<<< orphan*/  free_fs_struct (struct fs_struct*) ; 
 struct fs_struct init_fs ; 
 int /*<<< orphan*/  task_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  task_unlock (TYPE_1__*) ; 
 int /*<<< orphan*/  write_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock (int /*<<< orphan*/ *) ; 

void daemonize_fs_struct(void)
{
	struct fs_struct *fs = current->fs;

	if (fs) {
		int kill;

		task_lock(current);

		write_lock(&init_fs.lock);
		init_fs.users++;
		write_unlock(&init_fs.lock);

		write_lock(&fs->lock);
		current->fs = &init_fs;
		kill = !--fs->users;
		write_unlock(&fs->lock);

		task_unlock(current);
		if (kill)
			free_fs_struct(fs);
	}
}