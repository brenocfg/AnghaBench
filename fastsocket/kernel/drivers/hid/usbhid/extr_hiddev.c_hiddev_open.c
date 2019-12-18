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
struct inode {int dummy; } ;
struct hiddev_list {TYPE_1__* hiddev; int /*<<< orphan*/  node; int /*<<< orphan*/  thread_lock; } ;
struct hid_device {int dummy; } ;
struct file {struct hiddev_list* private_data; } ;
struct TYPE_2__ {struct hid_device* hid; scalar_t__ exist; int /*<<< orphan*/  open; int /*<<< orphan*/  list_lock; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int EIO ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int HIDDEV_MINORS ; 
 int HIDDEV_MINOR_BASE ; 
 TYPE_1__** hiddev_table ; 
 int iminor (struct inode*) ; 
 int /*<<< orphan*/  kfree (struct hiddev_list*) ; 
 struct hiddev_list* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int usbhid_get_power (struct hid_device*) ; 
 int usbhid_open (struct hid_device*) ; 

__attribute__((used)) static int hiddev_open(struct inode *inode, struct file *file)
{
	struct hiddev_list *list;
	int res;

	int i = iminor(inode) - HIDDEV_MINOR_BASE;

	if (i >= HIDDEV_MINORS || i < 0 || !hiddev_table[i])
		return -ENODEV;

	if (!(list = kzalloc(sizeof(struct hiddev_list), GFP_KERNEL)))
		return -ENOMEM;
	mutex_init(&list->thread_lock);

	list->hiddev = hiddev_table[i];


	file->private_data = list;

	/*
	 * no need for locking because the USB major number
	 * is shared which usbcore guards against disconnect
	 */
	if (list->hiddev->exist) {
		if (!list->hiddev->open++) {
			res = usbhid_open(hiddev_table[i]->hid);
			if (res < 0) {
				res = -EIO;
				goto bail;
			}
		}
	} else {
		res = -ENODEV;
		goto bail;
	}

	spin_lock_irq(&list->hiddev->list_lock);
	list_add_tail(&list->node, &hiddev_table[i]->list);
	spin_unlock_irq(&list->hiddev->list_lock);

	if (!list->hiddev->open++)
		if (list->hiddev->exist) {
			struct hid_device *hid = hiddev_table[i]->hid;
			res = usbhid_get_power(hid);
			if (res < 0) {
				res = -EIO;
				goto bail;
			}
			usbhid_open(hid);
		}

	return 0;
bail:
	file->private_data = NULL;
	kfree(list);
	return res;
}