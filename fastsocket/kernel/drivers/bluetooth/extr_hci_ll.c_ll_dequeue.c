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
struct sk_buff {int dummy; } ;
struct ll_struct {int /*<<< orphan*/  txq; } ;
struct hci_uart {struct ll_struct* priv; } ;

/* Variables and functions */
 struct sk_buff* skb_dequeue (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct sk_buff *ll_dequeue(struct hci_uart *hu)
{
	struct ll_struct *ll = hu->priv;
	return skb_dequeue(&ll->txq);
}