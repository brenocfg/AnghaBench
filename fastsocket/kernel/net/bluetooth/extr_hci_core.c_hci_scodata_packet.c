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
struct sk_buff {int /*<<< orphan*/  len; scalar_t__ data; } ;
struct hci_sco_hdr {int /*<<< orphan*/  handle; } ;
struct hci_proto {int /*<<< orphan*/  (* recv_scodata ) (struct hci_conn*,struct sk_buff*) ;} ;
struct TYPE_2__ {int /*<<< orphan*/  sco_rx; } ;
struct hci_dev {int /*<<< orphan*/  name; TYPE_1__ stat; } ;
struct hci_conn {int dummy; } ;
typedef  int /*<<< orphan*/  __u16 ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BT_ERR (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t HCI_PROTO_SCO ; 
 int /*<<< orphan*/  HCI_SCO_HDR_SIZE ; 
 int /*<<< orphan*/  __le16_to_cpu (int /*<<< orphan*/ ) ; 
 struct hci_conn* hci_conn_hash_lookup_handle (struct hci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_dev_lock (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_dev_unlock (struct hci_dev*) ; 
 struct hci_proto** hci_proto ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct hci_conn*,struct sk_buff*) ; 

__attribute__((used)) static inline void hci_scodata_packet(struct hci_dev *hdev, struct sk_buff *skb)
{
	struct hci_sco_hdr *hdr = (void *) skb->data;
	struct hci_conn *conn;
	__u16 handle;

	skb_pull(skb, HCI_SCO_HDR_SIZE);

	handle = __le16_to_cpu(hdr->handle);

	BT_DBG("%s len %d handle 0x%x", hdev->name, skb->len, handle);

	hdev->stat.sco_rx++;

	hci_dev_lock(hdev);
	conn = hci_conn_hash_lookup_handle(hdev, handle);
	hci_dev_unlock(hdev);

	if (conn) {
		register struct hci_proto *hp;

		/* Send to upper protocol */
		if ((hp = hci_proto[HCI_PROTO_SCO]) && hp->recv_scodata) {
			hp->recv_scodata(conn, skb);
			return;
		}
	} else {
		BT_ERR("%s SCO packet for unknown connection handle %d",
			hdev->name, handle);
	}

	kfree_skb(skb);
}