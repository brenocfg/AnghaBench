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
struct hci_ev_num_comp_pkts {int num_hndl; } ;
struct hci_dev {scalar_t__ acl_cnt; scalar_t__ acl_pkts; scalar_t__ sco_cnt; scalar_t__ sco_pkts; int /*<<< orphan*/  tx_task; int /*<<< orphan*/  name; } ;
struct hci_conn {scalar_t__ type; int /*<<< orphan*/  sent; } ;
typedef  scalar_t__ __u16 ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 scalar_t__ ACL_LINK ; 
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ,...) ; 
 scalar_t__ get_unaligned_le16 (int /*<<< orphan*/ ) ; 
 struct hci_conn* hci_conn_hash_lookup_handle (struct hci_dev*,scalar_t__) ; 
 int /*<<< orphan*/  hci_sched_tx (struct hci_dev*) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int) ; 
 int /*<<< orphan*/  tasklet_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_enable (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void hci_num_comp_pkts_evt(struct hci_dev *hdev, struct sk_buff *skb)
{
	struct hci_ev_num_comp_pkts *ev = (void *) skb->data;
	__le16 *ptr;
	int i;

	skb_pull(skb, sizeof(*ev));

	BT_DBG("%s num_hndl %d", hdev->name, ev->num_hndl);

	if (skb->len < ev->num_hndl * 4) {
		BT_DBG("%s bad parameters", hdev->name);
		return;
	}

	tasklet_disable(&hdev->tx_task);

	for (i = 0, ptr = (__le16 *) skb->data; i < ev->num_hndl; i++) {
		struct hci_conn *conn;
		__u16  handle, count;

		handle = get_unaligned_le16(ptr++);
		count  = get_unaligned_le16(ptr++);

		conn = hci_conn_hash_lookup_handle(hdev, handle);
		if (conn) {
			conn->sent -= count;

			if (conn->type == ACL_LINK) {
				if ((hdev->acl_cnt += count) > hdev->acl_pkts)
					hdev->acl_cnt = hdev->acl_pkts;
			} else {
				if ((hdev->sco_cnt += count) > hdev->sco_pkts)
					hdev->sco_cnt = hdev->sco_pkts;
			}
		}
	}

	hci_sched_tx(hdev);

	tasklet_enable(&hdev->tx_task);
}