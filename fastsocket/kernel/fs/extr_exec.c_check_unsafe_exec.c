#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct task_struct {TYPE_1__* fs; } ;
struct linux_binprm {int /*<<< orphan*/  unsafe; } ;
struct TYPE_2__ {unsigned int users; int in_exec; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int EAGAIN ; 
 int /*<<< orphan*/  LSM_UNSAFE_SHARE ; 
 struct task_struct* current ; 
 struct task_struct* next_thread (struct task_struct*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  tracehook_unsafe_exec (struct task_struct*) ; 
 int /*<<< orphan*/  write_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock (int /*<<< orphan*/ *) ; 

int check_unsafe_exec(struct linux_binprm *bprm)
{
	struct task_struct *p = current, *t;
	unsigned n_fs;
	int res = 0;

	bprm->unsafe = tracehook_unsafe_exec(p);

	n_fs = 1;
	write_lock(&p->fs->lock);
	rcu_read_lock();
	for (t = next_thread(p); t != p; t = next_thread(t)) {
		if (t->fs == p->fs)
			n_fs++;
	}
	rcu_read_unlock();

	if (p->fs->users > n_fs) {
		bprm->unsafe |= LSM_UNSAFE_SHARE;
	} else {
		res = -EAGAIN;
		if (!p->fs->in_exec) {
			p->fs->in_exec = 1;
			res = 1;
		}
	}
	write_unlock(&p->fs->lock);

	return res;
}