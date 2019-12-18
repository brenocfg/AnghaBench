#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u16 ;
struct sk_buff {scalar_t__ data; } ;
struct hci_event_hdr {scalar_t__ evt; } ;
struct hci_ev_cmd_complete {int /*<<< orphan*/  opcode; } ;
struct TYPE_3__ {int sendcmdflag; } ;
struct btmrvl_private {TYPE_2__* adapter; TYPE_1__ btmrvl_dev; } ;
struct TYPE_4__ {int cmd_complete; int /*<<< orphan*/  cmd_wait_q; } ;

/* Variables and functions */
 scalar_t__ BT_CMD_MODULE_CFG_REQ ; 
 scalar_t__ HCI_EVENT_HDR_SIZE ; 
 scalar_t__ HCI_EV_CMD_COMPLETE ; 
 scalar_t__ __le16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ hci_opcode_ocf (scalar_t__) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

void btmrvl_check_evtpkt(struct btmrvl_private *priv, struct sk_buff *skb)
{
	struct hci_event_hdr *hdr = (void *) skb->data;
	struct hci_ev_cmd_complete *ec;
	u16 opcode, ocf;

	if (hdr->evt == HCI_EV_CMD_COMPLETE) {
		ec = (void *) (skb->data + HCI_EVENT_HDR_SIZE);
		opcode = __le16_to_cpu(ec->opcode);
		ocf = hci_opcode_ocf(opcode);
		if (ocf == BT_CMD_MODULE_CFG_REQ &&
					priv->btmrvl_dev.sendcmdflag) {
			priv->btmrvl_dev.sendcmdflag = false;
			priv->adapter->cmd_complete = true;
			wake_up_interruptible(&priv->adapter->cmd_wait_q);
		}
	}
}