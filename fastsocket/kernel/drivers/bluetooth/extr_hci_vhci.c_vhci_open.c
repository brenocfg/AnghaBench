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
struct vhci_data {struct hci_dev* hdev; int /*<<< orphan*/  read_wait; int /*<<< orphan*/  readq; } ;
struct inode {int dummy; } ;
struct hci_dev {int /*<<< orphan*/  owner; int /*<<< orphan*/  destruct; int /*<<< orphan*/  send; int /*<<< orphan*/  flush; int /*<<< orphan*/  close; int /*<<< orphan*/  open; struct vhci_data* driver_data; int /*<<< orphan*/  type; } ;
struct file {struct vhci_data* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_ERR (char*) ; 
 int EBUSY ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HCI_VIRTUAL ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 struct hci_dev* hci_alloc_dev () ; 
 int /*<<< orphan*/  hci_free_dev (struct hci_dev*) ; 
 scalar_t__ hci_register_dev (struct hci_dev*) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct vhci_data*) ; 
 struct vhci_data* kzalloc (int,int /*<<< orphan*/ ) ; 
 int nonseekable_open (struct inode*,struct file*) ; 
 int /*<<< orphan*/  skb_queue_head_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vhci_close_dev ; 
 int /*<<< orphan*/  vhci_destruct ; 
 int /*<<< orphan*/  vhci_flush ; 
 int /*<<< orphan*/  vhci_open_dev ; 
 int /*<<< orphan*/  vhci_send_frame ; 

__attribute__((used)) static int vhci_open(struct inode *inode, struct file *file)
{
	struct vhci_data *data;
	struct hci_dev *hdev;

	data = kzalloc(sizeof(struct vhci_data), GFP_KERNEL);
	if (!data)
		return -ENOMEM;

	skb_queue_head_init(&data->readq);
	init_waitqueue_head(&data->read_wait);

	hdev = hci_alloc_dev();
	if (!hdev) {
		kfree(data);
		return -ENOMEM;
	}

	data->hdev = hdev;

	hdev->type = HCI_VIRTUAL;
	hdev->driver_data = data;

	hdev->open     = vhci_open_dev;
	hdev->close    = vhci_close_dev;
	hdev->flush    = vhci_flush;
	hdev->send     = vhci_send_frame;
	hdev->destruct = vhci_destruct;

	hdev->owner = THIS_MODULE;

	if (hci_register_dev(hdev) < 0) {
		BT_ERR("Can't register HCI device");
		kfree(data);
		hci_free_dev(hdev);
		return -EBUSY;
	}

	file->private_data = data;

	return nonseekable_open(inode, file);
}