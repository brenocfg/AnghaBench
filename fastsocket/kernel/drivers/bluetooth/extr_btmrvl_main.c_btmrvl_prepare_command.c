#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct sk_buff {void* dev; } ;
struct TYPE_4__ {int gpio_gap; scalar_t__ hsmode; scalar_t__ hscmd; scalar_t__ hcidev; scalar_t__ psmode; scalar_t__ pscmd; scalar_t__ hscfgcmd; } ;
struct btmrvl_private {int (* hw_wakeup_firmware ) (struct btmrvl_private*) ;TYPE_2__* adapter; TYPE_1__ btmrvl_dev; } ;
struct btmrvl_cmd {int length; int* data; void* ocf_ogf; } ;
struct TYPE_6__ {void* pkt_type; } ;
struct TYPE_5__ {int /*<<< orphan*/  hs_state; int /*<<< orphan*/  tx_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_CMD_AUTO_SLEEP_MODE ; 
 int /*<<< orphan*/  BT_CMD_HOST_SLEEP_CONFIG ; 
 int /*<<< orphan*/  BT_DBG (char*,int,...) ; 
 int /*<<< orphan*/  BT_ERR (char*) ; 
 int BT_PS_DISABLE ; 
 int BT_PS_ENABLE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  HS_DEACTIVATED ; 
 void* MRVL_VENDOR_PKT ; 
 int /*<<< orphan*/  OGF ; 
 TYPE_3__* bt_cb (struct sk_buff*) ; 
 struct sk_buff* bt_skb_alloc (int,int /*<<< orphan*/ ) ; 
 int btmrvl_enable_hs (struct btmrvl_private*) ; 
 void* cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_opcode_pack (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ skb_put (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_queue_head (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int stub1 (struct btmrvl_private*) ; 

int btmrvl_prepare_command(struct btmrvl_private *priv)
{
	struct sk_buff *skb = NULL;
	struct btmrvl_cmd *cmd;
	int ret = 0;

	if (priv->btmrvl_dev.hscfgcmd) {
		priv->btmrvl_dev.hscfgcmd = 0;

		skb = bt_skb_alloc(sizeof(*cmd), GFP_ATOMIC);
		if (skb == NULL) {
			BT_ERR("No free skb");
			return -ENOMEM;
		}

		cmd = (struct btmrvl_cmd *) skb_put(skb, sizeof(*cmd));
		cmd->ocf_ogf = cpu_to_le16(hci_opcode_pack(OGF, BT_CMD_HOST_SLEEP_CONFIG));
		cmd->length = 2;
		cmd->data[0] = (priv->btmrvl_dev.gpio_gap & 0xff00) >> 8;
		cmd->data[1] = (u8) (priv->btmrvl_dev.gpio_gap & 0x00ff);

		bt_cb(skb)->pkt_type = MRVL_VENDOR_PKT;

		skb->dev = (void *) priv->btmrvl_dev.hcidev;
		skb_queue_head(&priv->adapter->tx_queue, skb);

		BT_DBG("Queue HSCFG Command, gpio=0x%x, gap=0x%x",
						cmd->data[0], cmd->data[1]);
	}

	if (priv->btmrvl_dev.pscmd) {
		priv->btmrvl_dev.pscmd = 0;

		skb = bt_skb_alloc(sizeof(*cmd), GFP_ATOMIC);
		if (skb == NULL) {
			BT_ERR("No free skb");
			return -ENOMEM;
		}

		cmd = (struct btmrvl_cmd *) skb_put(skb, sizeof(*cmd));
		cmd->ocf_ogf = cpu_to_le16(hci_opcode_pack(OGF, BT_CMD_AUTO_SLEEP_MODE));
		cmd->length = 1;

		if (priv->btmrvl_dev.psmode)
			cmd->data[0] = BT_PS_ENABLE;
		else
			cmd->data[0] = BT_PS_DISABLE;

		bt_cb(skb)->pkt_type = MRVL_VENDOR_PKT;

		skb->dev = (void *) priv->btmrvl_dev.hcidev;
		skb_queue_head(&priv->adapter->tx_queue, skb);

		BT_DBG("Queue PSMODE Command:%d", cmd->data[0]);
	}

	if (priv->btmrvl_dev.hscmd) {
		priv->btmrvl_dev.hscmd = 0;

		if (priv->btmrvl_dev.hsmode) {
			ret = btmrvl_enable_hs(priv);
		} else {
			ret = priv->hw_wakeup_firmware(priv);
			priv->adapter->hs_state = HS_DEACTIVATED;
		}
	}

	return ret;
}