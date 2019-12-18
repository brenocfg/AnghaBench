#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {void* dev; } ;
struct TYPE_7__ {int sendcmdflag; scalar_t__ hcidev; } ;
struct TYPE_5__ {int /*<<< orphan*/  wait_q; } ;
struct btmrvl_private {TYPE_3__ btmrvl_dev; TYPE_2__* adapter; TYPE_1__ main_thread; } ;
struct btmrvl_cmd {int length; int* data; int /*<<< orphan*/  ocf_ogf; } ;
struct TYPE_8__ {int /*<<< orphan*/  pkt_type; } ;
struct TYPE_6__ {int cmd_complete; int /*<<< orphan*/  cmd_wait_q; int /*<<< orphan*/  tx_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_CMD_MODULE_CFG_REQ ; 
 int /*<<< orphan*/  BT_DBG (char*) ; 
 int /*<<< orphan*/  BT_ERR (char*,...) ; 
 int ENOMEM ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  MRVL_VENDOR_PKT ; 
 int /*<<< orphan*/  OGF ; 
 int /*<<< orphan*/  WAIT_UNTIL_CMD_RESP ; 
 TYPE_4__* bt_cb (struct sk_buff*) ; 
 struct sk_buff* bt_skb_alloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_opcode_pack (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 scalar_t__ skb_put (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_queue_head (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  wait_event_interruptible_timeout (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

int btmrvl_send_module_cfg_cmd(struct btmrvl_private *priv, int subcmd)
{
	struct sk_buff *skb;
	struct btmrvl_cmd *cmd;
	int ret = 0;

	skb = bt_skb_alloc(sizeof(*cmd), GFP_ATOMIC);
	if (skb == NULL) {
		BT_ERR("No free skb");
		return -ENOMEM;
	}

	cmd = (struct btmrvl_cmd *) skb_put(skb, sizeof(*cmd));
	cmd->ocf_ogf = cpu_to_le16(hci_opcode_pack(OGF, BT_CMD_MODULE_CFG_REQ));
	cmd->length = 1;
	cmd->data[0] = subcmd;

	bt_cb(skb)->pkt_type = MRVL_VENDOR_PKT;

	skb->dev = (void *) priv->btmrvl_dev.hcidev;
	skb_queue_head(&priv->adapter->tx_queue, skb);

	priv->btmrvl_dev.sendcmdflag = true;

	priv->adapter->cmd_complete = false;

	BT_DBG("Queue module cfg Command");

	wake_up_interruptible(&priv->main_thread.wait_q);

	if (!wait_event_interruptible_timeout(priv->adapter->cmd_wait_q,
				priv->adapter->cmd_complete,
				msecs_to_jiffies(WAIT_UNTIL_CMD_RESP))) {
		ret = -ETIMEDOUT;
		BT_ERR("module_cfg_cmd(%x): timeout: %d",
					subcmd, priv->btmrvl_dev.sendcmdflag);
	}

	BT_DBG("module cfg Command done");

	return ret;
}