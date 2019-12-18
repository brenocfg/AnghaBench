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
struct vhci_data {int /*<<< orphan*/  readq; } ;
struct hci_dev {struct vhci_data* driver_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  skb_queue_purge (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vhci_flush(struct hci_dev *hdev)
{
	struct vhci_data *data = hdev->driver_data;

	skb_queue_purge(&data->readq);

	return 0;
}