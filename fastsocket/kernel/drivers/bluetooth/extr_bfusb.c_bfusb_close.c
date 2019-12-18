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
 int /*<<< orphan*/  BT_DBG (char*,struct hci_dev*,struct bfusb_data*) ; 
 int /*<<< orphan*/  HCI_RUNNING ; 
 int /*<<< orphan*/  bfusb_flush (struct hci_dev*) ; 
 int /*<<< orphan*/  bfusb_unlink_urbs (struct bfusb_data*) ; 
 int /*<<< orphan*/  test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  write_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int bfusb_close(struct hci_dev *hdev)
{
	struct bfusb_data *data = hdev->driver_data;
	unsigned long flags;

	BT_DBG("hdev %p bfusb %p", hdev, data);

	if (!test_and_clear_bit(HCI_RUNNING, &hdev->flags))
		return 0;

	write_lock_irqsave(&data->lock, flags);
	write_unlock_irqrestore(&data->lock, flags);

	bfusb_unlink_urbs(data);
	bfusb_flush(hdev);

	return 0;
}