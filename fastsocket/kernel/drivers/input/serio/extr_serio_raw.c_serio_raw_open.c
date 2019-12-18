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
struct serio_raw_list {int /*<<< orphan*/  node; struct serio_raw* serio_raw; } ;
struct serio_raw {int /*<<< orphan*/  list; int /*<<< orphan*/  refcnt; int /*<<< orphan*/  serio; } ;
struct inode {int dummy; } ;
struct file {struct serio_raw_list* private_data; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  iminor (struct inode*) ; 
 struct serio_raw_list* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_kernel () ; 
 int mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct serio_raw* serio_raw_locate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serio_raw_mutex ; 
 int /*<<< orphan*/  unlock_kernel () ; 

__attribute__((used)) static int serio_raw_open(struct inode *inode, struct file *file)
{
	struct serio_raw *serio_raw;
	struct serio_raw_list *list;
	int retval = 0;

	lock_kernel();
	retval = mutex_lock_interruptible(&serio_raw_mutex);
	if (retval)
		goto out_bkl;

	if (!(serio_raw = serio_raw_locate(iminor(inode)))) {
		retval = -ENODEV;
		goto out;
	}

	if (!serio_raw->serio) {
		retval = -ENODEV;
		goto out;
	}

	if (!(list = kzalloc(sizeof(struct serio_raw_list), GFP_KERNEL))) {
		retval = -ENOMEM;
		goto out;
	}

	list->serio_raw = serio_raw;
	file->private_data = list;

	serio_raw->refcnt++;
	list_add_tail(&list->node, &serio_raw->list);

out:
	mutex_unlock(&serio_raw_mutex);
out_bkl:
	unlock_kernel();
	return retval;
}