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
struct inode {int dummy; } ;
struct hiddev_list {struct hiddev_list* hiddev; int /*<<< orphan*/  hid; scalar_t__ exist; int /*<<< orphan*/  open; int /*<<< orphan*/  list_lock; int /*<<< orphan*/  node; } ;
struct file {struct hiddev_list* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct hiddev_list*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  usbhid_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbhid_put_power (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hiddev_release(struct inode * inode, struct file * file)
{
	struct hiddev_list *list = file->private_data;
	unsigned long flags;

	spin_lock_irqsave(&list->hiddev->list_lock, flags);
	list_del(&list->node);
	spin_unlock_irqrestore(&list->hiddev->list_lock, flags);

	if (!--list->hiddev->open) {
		if (list->hiddev->exist) {
			usbhid_close(list->hiddev->hid);
			usbhid_put_power(list->hiddev->hid);
		} else {
			kfree(list->hiddev);
		}
	}

	kfree(list);

	return 0;
}