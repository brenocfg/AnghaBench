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
struct hci_uart {struct h4_struct* priv; } ;
struct h4_struct {int /*<<< orphan*/  rx_skb; int /*<<< orphan*/  txq; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct hci_uart*) ; 
 int /*<<< orphan*/  kfree (struct h4_struct*) ; 
 int /*<<< orphan*/  kfree_skb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_queue_purge (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int h4_close(struct hci_uart *hu)
{
	struct h4_struct *h4 = hu->priv;

	hu->priv = NULL;

	BT_DBG("hu %p", hu);

	skb_queue_purge(&h4->txq);

	kfree_skb(h4->rx_skb);

	hu->priv = NULL;
	kfree(h4);

	return 0;
}