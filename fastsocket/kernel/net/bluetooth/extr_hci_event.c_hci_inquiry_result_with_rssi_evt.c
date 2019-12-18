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
struct sk_buff {int len; scalar_t__ data; } ;
struct inquiry_info_with_rssi_and_pscan_mode {int pscan_mode; int /*<<< orphan*/  rssi; int /*<<< orphan*/  clock_offset; int /*<<< orphan*/  dev_class; int /*<<< orphan*/  pscan_period_mode; int /*<<< orphan*/  pscan_rep_mode; int /*<<< orphan*/  bdaddr; } ;
struct inquiry_info_with_rssi {int /*<<< orphan*/  rssi; int /*<<< orphan*/  clock_offset; int /*<<< orphan*/  dev_class; int /*<<< orphan*/  pscan_period_mode; int /*<<< orphan*/  pscan_rep_mode; int /*<<< orphan*/  bdaddr; } ;
struct inquiry_data {int pscan_mode; int ssp_mode; int /*<<< orphan*/  rssi; int /*<<< orphan*/  clock_offset; int /*<<< orphan*/  dev_class; int /*<<< orphan*/  pscan_period_mode; int /*<<< orphan*/  pscan_rep_mode; int /*<<< orphan*/  bdaddr; } ;
struct hci_dev {int /*<<< orphan*/  name; } ;
typedef  int __u8 ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bacpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hci_dev_lock (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_dev_unlock (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_inquiry_cache_update (struct hci_dev*,struct inquiry_data*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void hci_inquiry_result_with_rssi_evt(struct hci_dev *hdev, struct sk_buff *skb)
{
	struct inquiry_data data;
	int num_rsp = *((__u8 *) skb->data);

	BT_DBG("%s num_rsp %d", hdev->name, num_rsp);

	if (!num_rsp)
		return;

	hci_dev_lock(hdev);

	if ((skb->len - 1) / num_rsp != sizeof(struct inquiry_info_with_rssi)) {
		struct inquiry_info_with_rssi_and_pscan_mode *info = (void *) (skb->data + 1);

		for (; num_rsp; num_rsp--) {
			bacpy(&data.bdaddr, &info->bdaddr);
			data.pscan_rep_mode	= info->pscan_rep_mode;
			data.pscan_period_mode	= info->pscan_period_mode;
			data.pscan_mode		= info->pscan_mode;
			memcpy(data.dev_class, info->dev_class, 3);
			data.clock_offset	= info->clock_offset;
			data.rssi		= info->rssi;
			data.ssp_mode		= 0x00;
			info++;
			hci_inquiry_cache_update(hdev, &data);
		}
	} else {
		struct inquiry_info_with_rssi *info = (void *) (skb->data + 1);

		for (; num_rsp; num_rsp--) {
			bacpy(&data.bdaddr, &info->bdaddr);
			data.pscan_rep_mode	= info->pscan_rep_mode;
			data.pscan_period_mode	= info->pscan_period_mode;
			data.pscan_mode		= 0x00;
			memcpy(data.dev_class, info->dev_class, 3);
			data.clock_offset	= info->clock_offset;
			data.rssi		= info->rssi;
			data.ssp_mode		= 0x00;
			info++;
			hci_inquiry_cache_update(hdev, &data);
		}
	}

	hci_dev_unlock(hdev);
}