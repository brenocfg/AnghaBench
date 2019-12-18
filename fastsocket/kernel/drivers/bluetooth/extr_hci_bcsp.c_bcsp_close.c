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
struct hci_uart {struct bcsp_struct* priv; } ;
struct bcsp_struct {int /*<<< orphan*/  tbcsp; int /*<<< orphan*/  unrel; int /*<<< orphan*/  rel; int /*<<< orphan*/  unack; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct hci_uart*) ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct bcsp_struct*) ; 
 int /*<<< orphan*/  skb_queue_purge (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bcsp_close(struct hci_uart *hu)
{
	struct bcsp_struct *bcsp = hu->priv;
	hu->priv = NULL;

	BT_DBG("hu %p", hu);

	skb_queue_purge(&bcsp->unack);
	skb_queue_purge(&bcsp->rel);
	skb_queue_purge(&bcsp->unrel);
	del_timer(&bcsp->tbcsp);

	kfree(bcsp);
	return 0;
}