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
struct TYPE_2__ {scalar_t__ sco_num; } ;
struct hci_dev {TYPE_1__ conn_hash; int /*<<< orphan*/  name; struct btusb_data* driver_data; } ;
struct btusb_data {scalar_t__ sco_num; int /*<<< orphan*/  work; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void btusb_notify(struct hci_dev *hdev, unsigned int evt)
{
	struct btusb_data *data = hdev->driver_data;

	BT_DBG("%s evt %d", hdev->name, evt);

	if (hdev->conn_hash.sco_num != data->sco_num) {
		data->sco_num = hdev->conn_hash.sco_num;
		schedule_work(&data->work);
	}
}