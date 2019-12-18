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
struct vfsmount {int dummy; } ;
struct super_block {int s_flags; TYPE_1__* s_root; } ;
struct proc_inode {scalar_t__ pid; } ;
struct pid_namespace {int dummy; } ;
struct file_system_type {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  d_inode; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IS_ERR (struct super_block*) ; 
 int MS_ACTIVE ; 
 int MS_KERNMOUNT ; 
 struct proc_inode* PROC_I (int /*<<< orphan*/ ) ; 
 int PTR_ERR (struct super_block*) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  deactivate_locked_super (struct super_block*) ; 
 int /*<<< orphan*/  find_pid_ns (int,struct pid_namespace*) ; 
 scalar_t__ get_pid (int /*<<< orphan*/ ) ; 
 int proc_fill_super (struct super_block*) ; 
 int /*<<< orphan*/  proc_parse_options (char*,struct pid_namespace*) ; 
 int /*<<< orphan*/  proc_set_super ; 
 int /*<<< orphan*/  proc_test_super ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 struct super_block* sget (struct file_system_type*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct pid_namespace*) ; 
 int /*<<< orphan*/  simple_set_mnt (struct vfsmount*,struct super_block*) ; 
 struct pid_namespace* task_active_pid_ns (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int proc_get_sb(struct file_system_type *fs_type,
	int flags, const char *dev_name, void *data, struct vfsmount *mnt)
{
	int err;
	struct super_block *sb;
	struct pid_namespace *ns;
	struct proc_inode *ei;
	char *options;

	if (flags & MS_KERNMOUNT) {
		ns = (struct pid_namespace *)data;
		options = NULL;
	} else {
		ns = task_active_pid_ns(current);
		options = data;
	}

	sb = sget(fs_type, proc_test_super, proc_set_super, ns);
	if (IS_ERR(sb))
		return PTR_ERR(sb);

	if (!sb->s_root) {
		sb->s_flags = flags;
		if (!proc_parse_options(options, ns)) {
			deactivate_locked_super(sb);
			return -EINVAL;
		}
		err = proc_fill_super(sb);
		if (err) {
			deactivate_locked_super(sb);
			return err;
		}

		sb->s_flags |= MS_ACTIVE;
	}
	ei = PROC_I(sb->s_root->d_inode);
	if (!ei->pid) {
		rcu_read_lock();
		ei->pid = get_pid(find_pid_ns(1, ns));
		rcu_read_unlock();
	}

	simple_set_mnt(mnt, sb);
	return 0;
}