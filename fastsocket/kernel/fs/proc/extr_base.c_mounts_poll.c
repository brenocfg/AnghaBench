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
struct proc_mounts {scalar_t__ event; struct mnt_namespace* ns; } ;
struct mnt_namespace {scalar_t__ event; int /*<<< orphan*/  poll; } ;
struct file {struct proc_mounts* private_data; } ;
typedef  int /*<<< orphan*/  poll_table ;

/* Variables and functions */
 unsigned int POLLERR ; 
 unsigned int POLLIN ; 
 unsigned int POLLPRI ; 
 unsigned int POLLRDNORM ; 
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vfsmount_lock ; 

__attribute__((used)) static unsigned mounts_poll(struct file *file, poll_table *wait)
{
	struct proc_mounts *p = file->private_data;
	struct mnt_namespace *ns = p->ns;
	unsigned res = POLLIN | POLLRDNORM;

	poll_wait(file, &ns->poll, wait);

	spin_lock(&vfsmount_lock);
	if (p->event != ns->event) {
		p->event = ns->event;
		res |= POLLERR | POLLPRI;
	}
	spin_unlock(&vfsmount_lock);

	return res;
}