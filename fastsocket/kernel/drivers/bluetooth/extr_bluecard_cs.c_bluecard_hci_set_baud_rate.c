#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct hci_dev {scalar_t__ driver_data; } ;
typedef  int /*<<< orphan*/  cmd ;
struct TYPE_4__ {int /*<<< orphan*/  txq; } ;
typedef  TYPE_1__ bluecard_info_t ;
struct TYPE_5__ {int /*<<< orphan*/  pkt_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_ERR (char*) ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int HCI_COMMAND_PKT ; 
 int /*<<< orphan*/  HCI_MAX_FRAME_SIZE ; 
 int /*<<< orphan*/  PKT_BAUD_RATE_115200 ; 
 int /*<<< orphan*/  PKT_BAUD_RATE_230400 ; 
 int /*<<< orphan*/  PKT_BAUD_RATE_460800 ; 
 int /*<<< orphan*/  PKT_BAUD_RATE_57600 ; 
 int /*<<< orphan*/  bluecard_write_wakeup (TYPE_1__*) ; 
 TYPE_2__* bt_cb (struct sk_buff*) ; 
 struct sk_buff* bt_skb_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,unsigned char*,int) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 

__attribute__((used)) static int bluecard_hci_set_baud_rate(struct hci_dev *hdev, int baud)
{
	bluecard_info_t *info = (bluecard_info_t *)(hdev->driver_data);
	struct sk_buff *skb;

	/* Ericsson baud rate command */
	unsigned char cmd[] = { HCI_COMMAND_PKT, 0x09, 0xfc, 0x01, 0x03 };

	if (!(skb = bt_skb_alloc(HCI_MAX_FRAME_SIZE, GFP_ATOMIC))) {
		BT_ERR("Can't allocate mem for new packet");
		return -1;
	}

	switch (baud) {
	case 460800:
		cmd[4] = 0x00;
		bt_cb(skb)->pkt_type = PKT_BAUD_RATE_460800;
		break;
	case 230400:
		cmd[4] = 0x01;
		bt_cb(skb)->pkt_type = PKT_BAUD_RATE_230400;
		break;
	case 115200:
		cmd[4] = 0x02;
		bt_cb(skb)->pkt_type = PKT_BAUD_RATE_115200;
		break;
	case 57600:
		/* Fall through... */
	default:
		cmd[4] = 0x03;
		bt_cb(skb)->pkt_type = PKT_BAUD_RATE_57600;
		break;
	}

	memcpy(skb_put(skb, sizeof(cmd)), cmd, sizeof(cmd));

	skb_queue_tail(&(info->txq), skb);

	bluecard_write_wakeup(info);

	return 0;
}