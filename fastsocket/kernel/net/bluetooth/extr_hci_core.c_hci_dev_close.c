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
struct hci_dev {int dummy; } ;
typedef  int /*<<< orphan*/  __u16 ;

/* Variables and functions */
 int ENODEV ; 
 int hci_dev_do_close (struct hci_dev*) ; 
 struct hci_dev* hci_dev_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_dev_put (struct hci_dev*) ; 

int hci_dev_close(__u16 dev)
{
	struct hci_dev *hdev;
	int err;

	if (!(hdev = hci_dev_get(dev)))
		return -ENODEV;
	err = hci_dev_do_close(hdev);
	hci_dev_put(hdev);
	return err;
}