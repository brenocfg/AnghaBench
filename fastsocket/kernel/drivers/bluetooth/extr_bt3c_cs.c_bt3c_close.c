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
struct hci_dev {int /*<<< orphan*/  name; } ;
struct TYPE_3__ {struct hci_dev* hdev; } ;
typedef  TYPE_1__ bt3c_info_t ;

/* Variables and functions */
 int /*<<< orphan*/  BT_ERR (char*,int /*<<< orphan*/ ) ; 
 int ENODEV ; 
 int /*<<< orphan*/  bt3c_hci_close (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_free_dev (struct hci_dev*) ; 
 scalar_t__ hci_unregister_dev (struct hci_dev*) ; 

__attribute__((used)) static int bt3c_close(bt3c_info_t *info)
{
	struct hci_dev *hdev = info->hdev;

	if (!hdev)
		return -ENODEV;

	bt3c_hci_close(hdev);

	if (hci_unregister_dev(hdev) < 0)
		BT_ERR("Can't unregister HCI device %s", hdev->name);

	hci_free_dev(hdev);

	return 0;
}