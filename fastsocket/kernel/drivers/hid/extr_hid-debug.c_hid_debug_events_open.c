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
struct inode {scalar_t__ i_private; } ;
struct hid_device {int /*<<< orphan*/  debug_list; } ;
struct hid_debug_list {struct hid_device* hdev; int /*<<< orphan*/  node; int /*<<< orphan*/  read_mutex; void* hid_debug_buf; } ;
struct file {struct hid_debug_list* private_data; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int HID_DEBUG_BUFSIZE ; 
 int /*<<< orphan*/  kfree (struct hid_debug_list*) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hid_debug_events_open(struct inode *inode, struct file *file)
{
	int err = 0;
	struct hid_debug_list *list;

	if (!(list = kzalloc(sizeof(struct hid_debug_list), GFP_KERNEL))) {
		err = -ENOMEM;
		goto out;
	}

	if (!(list->hid_debug_buf = kzalloc(sizeof(char) * HID_DEBUG_BUFSIZE, GFP_KERNEL))) {
		err = -ENOMEM;
		kfree(list);
		goto out;
	}
	list->hdev = (struct hid_device *) inode->i_private;
	file->private_data = list;
	mutex_init(&list->read_mutex);

	list_add_tail(&list->node, &list->hdev->debug_list);

out:
	return err;
}