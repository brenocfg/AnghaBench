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
struct inode {int dummy; } ;
struct hidraw_list {struct hidraw_list* hidraw; scalar_t__ exist; int /*<<< orphan*/  node; } ;
struct hidraw {TYPE_2__* hid; int /*<<< orphan*/  open; } ;
struct file {struct hidraw_list* private_data; } ;
struct TYPE_5__ {TYPE_1__* ll_driver; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* close ) (TYPE_2__*) ;int /*<<< orphan*/  (* power ) (TYPE_2__*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  PM_HINT_NORMAL ; 
 struct hidraw** hidraw_table ; 
 unsigned int iminor (struct inode*) ; 
 int /*<<< orphan*/  kfree (struct hidraw_list*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  minors_lock ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__*) ; 

__attribute__((used)) static int hidraw_release(struct inode * inode, struct file * file)
{
	unsigned int minor = iminor(inode);
	struct hidraw *dev;
	struct hidraw_list *list = file->private_data;
	int ret;

	mutex_lock(&minors_lock);
	if (!hidraw_table[minor]) {
		ret = -ENODEV;
		goto unlock;
	}

	list_del(&list->node);
	dev = hidraw_table[minor];
	if (!--dev->open) {
		if (list->hidraw->exist) {
			if (dev->hid->ll_driver->power)
				dev->hid->ll_driver->power(dev->hid, PM_HINT_NORMAL);
			dev->hid->ll_driver->close(dev->hid);
		} else {
			kfree(list->hidraw);
		}
	}
	kfree(list);
	ret = 0;
unlock:
	mutex_unlock(&minors_lock);

	return ret;
}