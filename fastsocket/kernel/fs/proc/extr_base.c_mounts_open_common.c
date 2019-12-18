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
struct task_struct {int dummy; } ;
struct seq_operations {int dummy; } ;
struct path {int dummy; } ;
struct TYPE_2__ {struct proc_mounts* private; } ;
struct proc_mounts {int /*<<< orphan*/  event; struct path root; struct mnt_namespace* ns; TYPE_1__ m; } ;
struct nsproxy {struct mnt_namespace* mnt_ns; } ;
struct mnt_namespace {int /*<<< orphan*/  event; } ;
struct inode {int dummy; } ;
struct file {TYPE_1__* private_data; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ get_fs_path (struct task_struct*,struct path*,int) ; 
 int /*<<< orphan*/  get_mnt_ns (struct mnt_namespace*) ; 
 struct task_struct* get_proc_task (struct inode*) ; 
 int /*<<< orphan*/  kfree (struct proc_mounts*) ; 
 struct proc_mounts* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  path_put (struct path*) ; 
 int /*<<< orphan*/  put_mnt_ns (struct mnt_namespace*) ; 
 int /*<<< orphan*/  put_task_struct (struct task_struct*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int seq_open (struct file*,struct seq_operations const*) ; 
 struct nsproxy* task_nsproxy (struct task_struct*) ; 

__attribute__((used)) static int mounts_open_common(struct inode *inode, struct file *file,
			      const struct seq_operations *op)
{
	struct task_struct *task = get_proc_task(inode);
	struct nsproxy *nsp;
	struct mnt_namespace *ns = NULL;
	struct path root;
	struct proc_mounts *p;
	int ret = -EINVAL;

	if (task) {
		rcu_read_lock();
		nsp = task_nsproxy(task);
		if (nsp) {
			ns = nsp->mnt_ns;
			if (ns)
				get_mnt_ns(ns);
		}
		rcu_read_unlock();
		if (ns && get_fs_path(task, &root, 1) == 0)
			ret = 0;
		put_task_struct(task);
	}

	if (!ns)
		goto err;
	if (ret)
		goto err_put_ns;

	ret = -ENOMEM;
	p = kmalloc(sizeof(struct proc_mounts), GFP_KERNEL);
	if (!p)
		goto err_put_path;

	file->private_data = &p->m;
	ret = seq_open(file, op);
	if (ret)
		goto err_free;

	p->m.private = p;
	p->ns = ns;
	p->root = root;
	p->event = ns->event;

	return 0;

 err_free:
	kfree(p);
 err_put_path:
	path_put(&root);
 err_put_ns:
	put_mnt_ns(ns);
 err:
	return ret;
}