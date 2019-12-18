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
struct hci_dev {scalar_t__ rfkill; int /*<<< orphan*/ * reassembly; int /*<<< orphan*/  list; int /*<<< orphan*/  type; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct hci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HCI_DEV_UNREG ; 
 int /*<<< orphan*/  __hci_dev_put (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_dev_do_close (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_dev_list_lock ; 
 int /*<<< orphan*/  hci_notify (struct hci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_unregister_sysfs (struct hci_dev*) ; 
 int /*<<< orphan*/  kfree_skb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rfkill_destroy (scalar_t__) ; 
 int /*<<< orphan*/  rfkill_unregister (scalar_t__) ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

int hci_unregister_dev(struct hci_dev *hdev)
{
	int i;

	BT_DBG("%p name %s type %d", hdev, hdev->name, hdev->type);

	write_lock_bh(&hci_dev_list_lock);
	list_del(&hdev->list);
	write_unlock_bh(&hci_dev_list_lock);

	hci_dev_do_close(hdev);

	for (i = 0; i < 3; i++)
		kfree_skb(hdev->reassembly[i]);

	hci_notify(hdev, HCI_DEV_UNREG);

	if (hdev->rfkill) {
		rfkill_unregister(hdev->rfkill);
		rfkill_destroy(hdev->rfkill);
	}

	hci_unregister_sysfs(hdev);

	__hci_dev_put(hdev);

	return 0;
}