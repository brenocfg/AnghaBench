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
struct hci_dev {int /*<<< orphan*/  flags; struct bfusb_data* driver_data; } ;
struct bfusb_data {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int BFUSB_MAX_BULK_RX ; 
 int /*<<< orphan*/  BT_DBG (char*,struct hci_dev*,struct bfusb_data*) ; 
 int /*<<< orphan*/  HCI_RUNNING ; 
 int bfusb_rx_submit (struct bfusb_data*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  write_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int bfusb_open(struct hci_dev *hdev)
{
	struct bfusb_data *data = hdev->driver_data;
	unsigned long flags;
	int i, err;

	BT_DBG("hdev %p bfusb %p", hdev, data);

	if (test_and_set_bit(HCI_RUNNING, &hdev->flags))
		return 0;

	write_lock_irqsave(&data->lock, flags);

	err = bfusb_rx_submit(data, NULL);
	if (!err) {
		for (i = 1; i < BFUSB_MAX_BULK_RX; i++)
			bfusb_rx_submit(data, NULL);
	} else {
		clear_bit(HCI_RUNNING, &hdev->flags);
	}

	write_unlock_irqrestore(&data->lock, flags);

	return err;
}