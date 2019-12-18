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
struct sk_buff {scalar_t__ data; } ;
struct TYPE_2__ {int ssp_mode; } ;
struct inquiry_entry {TYPE_1__ data; } ;
struct hci_ev_remote_host_features {int* features; int /*<<< orphan*/  bdaddr; } ;
struct hci_dev {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_dev_lock (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_dev_unlock (struct hci_dev*) ; 
 struct inquiry_entry* hci_inquiry_cache_lookup (struct hci_dev*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void hci_remote_host_features_evt(struct hci_dev *hdev, struct sk_buff *skb)
{
	struct hci_ev_remote_host_features *ev = (void *) skb->data;
	struct inquiry_entry *ie;

	BT_DBG("%s", hdev->name);

	hci_dev_lock(hdev);

	if ((ie = hci_inquiry_cache_lookup(hdev, &ev->bdaddr)))
		ie->data.ssp_mode = (ev->features[0] & 0x01);

	hci_dev_unlock(hdev);
}