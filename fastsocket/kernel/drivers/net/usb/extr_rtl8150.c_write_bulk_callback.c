#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct urb {int status; TYPE_1__* dev; TYPE_2__* context; } ;
struct TYPE_6__ {TYPE_3__* netdev; int /*<<< orphan*/  tx_skb; } ;
typedef  TYPE_2__ rtl8150_t ;
struct TYPE_7__ {int /*<<< orphan*/  trans_start; int /*<<< orphan*/  name; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_kfree_skb_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  netif_device_present (TYPE_3__*) ; 
 int /*<<< orphan*/  netif_wake_queue (TYPE_3__*) ; 

__attribute__((used)) static void write_bulk_callback(struct urb *urb)
{
	rtl8150_t *dev;
	int status = urb->status;

	dev = urb->context;
	if (!dev)
		return;
	dev_kfree_skb_irq(dev->tx_skb);
	if (!netif_device_present(dev->netdev))
		return;
	if (status)
		dev_info(&urb->dev->dev, "%s: Tx status %d\n",
			 dev->netdev->name, status);
	dev->netdev->trans_start = jiffies;
	netif_wake_queue(dev->netdev);
}