#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vhost_dev {int /*<<< orphan*/ * mm; struct task_struct* worker; } ;
struct task_struct {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  pid; } ;

/* Variables and functions */
 int EBUSY ; 
 scalar_t__ IS_ERR (struct task_struct*) ; 
 int PTR_ERR (struct task_struct*) ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/ * get_task_mm (TYPE_1__*) ; 
 struct task_struct* kthread_create (int /*<<< orphan*/ ,struct vhost_dev*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kthread_stop (struct task_struct*) ; 
 int /*<<< orphan*/  mmput (int /*<<< orphan*/ *) ; 
 int vhost_attach_cgroups (struct vhost_dev*) ; 
 int vhost_dev_alloc_iovecs (struct vhost_dev*) ; 
 int /*<<< orphan*/  vhost_worker ; 
 int /*<<< orphan*/  wake_up_process (struct task_struct*) ; 

__attribute__((used)) static long vhost_dev_set_owner(struct vhost_dev *dev)
{
	struct task_struct *worker;
	int err;
	/* Is there an owner already? */
	if (dev->mm) {
		err = -EBUSY;
		goto err_mm;
	}
	/* No owner, become one */
	dev->mm = get_task_mm(current);
	worker = kthread_create(vhost_worker, dev, "vhost-%d", current->pid);
	if (IS_ERR(worker)) {
		err = PTR_ERR(worker);
		goto err_worker;
	}

	dev->worker = worker;
	wake_up_process(worker);	/* avoid contributing to loadavg */

	err = vhost_attach_cgroups(dev);
	if (err)
		goto err_cgroup;

	err = vhost_dev_alloc_iovecs(dev);
	if (err)
		goto err_cgroup;

	return 0;
err_cgroup:
	kthread_stop(worker);
	dev->worker = NULL;
err_worker:
	if (dev->mm)
		mmput(dev->mm);
	dev->mm = NULL;
err_mm:
	return err;
}