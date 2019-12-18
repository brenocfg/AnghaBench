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
struct rfcomm_dev {int /*<<< orphan*/  dst; int /*<<< orphan*/  src; } ;
struct hci_dev {int dummy; } ;
struct device {int dummy; } ;
struct hci_conn {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACL_LINK ; 
 struct hci_conn* hci_conn_hash_lookup_ba (struct hci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hci_dev_put (struct hci_dev*) ; 
 struct hci_dev* hci_get_route (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct device *rfcomm_get_device(struct rfcomm_dev *dev)
{
	struct hci_dev *hdev;
	struct hci_conn *conn;

	hdev = hci_get_route(&dev->dst, &dev->src);
	if (!hdev)
		return NULL;

	conn = hci_conn_hash_lookup_ba(hdev, ACL_LINK, &dev->dst);

	hci_dev_put(hdev);

	return conn ? &conn->dev : NULL;
}