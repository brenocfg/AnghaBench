#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int len; int /*<<< orphan*/  data; } ;
struct TYPE_10__ {TYPE_3__* hdev; int /*<<< orphan*/  tx_state; int /*<<< orphan*/  txq; TYPE_5__* p_dev; } ;
typedef  TYPE_4__ bt3c_info_t ;
struct TYPE_7__ {unsigned int BasePort1; } ;
struct TYPE_11__ {TYPE_1__ io; } ;
struct TYPE_8__ {int byte_tx; } ;
struct TYPE_9__ {TYPE_2__ stat; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_ERR (char*) ; 
 int /*<<< orphan*/  XMIT_SENDING ; 
 int bt3c_write (unsigned int,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  pcmcia_dev_present (TYPE_5__*) ; 
 struct sk_buff* skb_dequeue (int /*<<< orphan*/ *) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void bt3c_write_wakeup(bt3c_info_t *info)
{
	if (!info) {
		BT_ERR("Unknown device");
		return;
	}

	if (test_and_set_bit(XMIT_SENDING, &(info->tx_state)))
		return;

	do {
		register unsigned int iobase = info->p_dev->io.BasePort1;
		register struct sk_buff *skb;
		register int len;

		if (!pcmcia_dev_present(info->p_dev))
			break;


		if (!(skb = skb_dequeue(&(info->txq)))) {
			clear_bit(XMIT_SENDING, &(info->tx_state));
			break;
		}

		/* Send frame */
		len = bt3c_write(iobase, 256, skb->data, skb->len);

		if (len != skb->len) {
			BT_ERR("Very strange");
		}

		kfree_skb(skb);

		info->hdev->stat.byte_tx += len;

	} while (0);
}