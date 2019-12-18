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
struct tty_struct {TYPE_1__* ops; int /*<<< orphan*/  flags; } ;
struct sk_buff {int len; int /*<<< orphan*/  data; } ;
struct hci_uart {int /*<<< orphan*/  tx_state; struct sk_buff* tx_skb; struct hci_dev* hdev; struct tty_struct* tty; } ;
struct TYPE_5__ {int byte_tx; } ;
struct hci_dev {TYPE_2__ stat; } ;
struct TYPE_6__ {int /*<<< orphan*/  pkt_type; } ;
struct TYPE_4__ {int (* write ) (struct tty_struct*,int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*) ; 
 int /*<<< orphan*/  HCI_UART_SENDING ; 
 int /*<<< orphan*/  HCI_UART_TX_WAKEUP ; 
 int /*<<< orphan*/  TTY_DO_WRITE_WAKEUP ; 
 TYPE_3__* bt_cb (struct sk_buff*) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct sk_buff* hci_uart_dequeue (struct hci_uart*) ; 
 int /*<<< orphan*/  hci_uart_tx_complete (struct hci_uart*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int) ; 
 int stub1 (struct tty_struct*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int hci_uart_tx_wakeup(struct hci_uart *hu)
{
	struct tty_struct *tty = hu->tty;
	struct hci_dev *hdev = hu->hdev;
	struct sk_buff *skb;

	if (test_and_set_bit(HCI_UART_SENDING, &hu->tx_state)) {
		set_bit(HCI_UART_TX_WAKEUP, &hu->tx_state);
		return 0;
	}

	BT_DBG("");

restart:
	clear_bit(HCI_UART_TX_WAKEUP, &hu->tx_state);

	while ((skb = hci_uart_dequeue(hu))) {
		int len;

		set_bit(TTY_DO_WRITE_WAKEUP, &tty->flags);
		len = tty->ops->write(tty, skb->data, skb->len);
		hdev->stat.byte_tx += len;

		skb_pull(skb, len);
		if (skb->len) {
			hu->tx_skb = skb;
			break;
		}

		hci_uart_tx_complete(hu, bt_cb(skb)->pkt_type);
		kfree_skb(skb);
	}

	if (test_bit(HCI_UART_TX_WAKEUP, &hu->tx_state))
		goto restart;

	clear_bit(HCI_UART_SENDING, &hu->tx_state);
	return 0;
}