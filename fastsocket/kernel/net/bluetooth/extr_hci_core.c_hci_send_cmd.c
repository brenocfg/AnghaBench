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
struct sk_buff {void* dev; int /*<<< orphan*/  len; } ;
struct hci_dev {int /*<<< orphan*/  cmd_q; int /*<<< orphan*/  name; } ;
struct hci_command_hdr {int plen; int /*<<< orphan*/  opcode; } ;
typedef  int __u32 ;
typedef  int /*<<< orphan*/  __u16 ;
struct TYPE_2__ {int /*<<< orphan*/  pkt_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  BT_ERR (char*,int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int HCI_COMMAND_HDR_SIZE ; 
 int /*<<< orphan*/  HCI_COMMAND_PKT ; 
 TYPE_1__* bt_cb (struct sk_buff*) ; 
 struct sk_buff* bt_skb_alloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_sched_cmd (struct hci_dev*) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,void*,int) ; 
 scalar_t__ skb_put (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 

int hci_send_cmd(struct hci_dev *hdev, __u16 opcode, __u32 plen, void *param)
{
	int len = HCI_COMMAND_HDR_SIZE + plen;
	struct hci_command_hdr *hdr;
	struct sk_buff *skb;

	BT_DBG("%s opcode 0x%x plen %d", hdev->name, opcode, plen);

	skb = bt_skb_alloc(len, GFP_ATOMIC);
	if (!skb) {
		BT_ERR("%s no memory for command", hdev->name);
		return -ENOMEM;
	}

	hdr = (struct hci_command_hdr *) skb_put(skb, HCI_COMMAND_HDR_SIZE);
	hdr->opcode = cpu_to_le16(opcode);
	hdr->plen   = plen;

	if (plen)
		memcpy(skb_put(skb, plen), param, plen);

	BT_DBG("skb len %d", skb->len);

	bt_cb(skb)->pkt_type = HCI_COMMAND_PKT;
	skb->dev = (void *) hdev;
	skb_queue_tail(&hdev->cmd_q, skb);
	hci_sched_cmd(hdev);

	return 0;
}