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
struct sk_buff {scalar_t__ data; } ;
struct hci_rp_read_local_features {int /*<<< orphan*/  features; scalar_t__ status; } ;
struct hci_dev {int* features; int pkt_type; int esco_type; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ,int,...) ; 
 int ESCO_2EV3 ; 
 int ESCO_2EV5 ; 
 int ESCO_3EV3 ; 
 int ESCO_3EV5 ; 
 int ESCO_EV3 ; 
 int ESCO_EV4 ; 
 int ESCO_EV5 ; 
 int ESCO_HV2 ; 
 int ESCO_HV3 ; 
 int HCI_DH3 ; 
 int HCI_DH5 ; 
 int HCI_DM3 ; 
 int HCI_DM5 ; 
 int HCI_HV2 ; 
 int HCI_HV3 ; 
 int LMP_3SLOT ; 
 int LMP_5SLOT ; 
 int LMP_EDR_3S_ESCO ; 
 int LMP_EDR_ESCO_2M ; 
 int LMP_EDR_ESCO_3M ; 
 int LMP_ESCO ; 
 int LMP_EV4 ; 
 int LMP_EV5 ; 
 int LMP_HV2 ; 
 int LMP_HV3 ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void hci_cc_read_local_features(struct hci_dev *hdev, struct sk_buff *skb)
{
	struct hci_rp_read_local_features *rp = (void *) skb->data;

	BT_DBG("%s status 0x%x", hdev->name, rp->status);

	if (rp->status)
		return;

	memcpy(hdev->features, rp->features, 8);

	/* Adjust default settings according to features
	 * supported by device. */

	if (hdev->features[0] & LMP_3SLOT)
		hdev->pkt_type |= (HCI_DM3 | HCI_DH3);

	if (hdev->features[0] & LMP_5SLOT)
		hdev->pkt_type |= (HCI_DM5 | HCI_DH5);

	if (hdev->features[1] & LMP_HV2) {
		hdev->pkt_type  |= (HCI_HV2);
		hdev->esco_type |= (ESCO_HV2);
	}

	if (hdev->features[1] & LMP_HV3) {
		hdev->pkt_type  |= (HCI_HV3);
		hdev->esco_type |= (ESCO_HV3);
	}

	if (hdev->features[3] & LMP_ESCO)
		hdev->esco_type |= (ESCO_EV3);

	if (hdev->features[4] & LMP_EV4)
		hdev->esco_type |= (ESCO_EV4);

	if (hdev->features[4] & LMP_EV5)
		hdev->esco_type |= (ESCO_EV5);

	if (hdev->features[5] & LMP_EDR_ESCO_2M)
		hdev->esco_type |= (ESCO_2EV3);

	if (hdev->features[5] & LMP_EDR_ESCO_3M)
		hdev->esco_type |= (ESCO_3EV3);

	if (hdev->features[5] & LMP_EDR_3S_ESCO)
		hdev->esco_type |= (ESCO_2EV5 | ESCO_3EV5);

	BT_DBG("%s features 0x%.2x%.2x%.2x%.2x%.2x%.2x%.2x%.2x", hdev->name,
					hdev->features[0], hdev->features[1],
					hdev->features[2], hdev->features[3],
					hdev->features[4], hdev->features[5],
					hdev->features[6], hdev->features[7]);
}