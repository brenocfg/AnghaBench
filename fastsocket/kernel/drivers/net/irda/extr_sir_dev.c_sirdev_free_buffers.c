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
struct TYPE_4__ {int /*<<< orphan*/ * skb; int /*<<< orphan*/  head; } ;
struct TYPE_3__ {int /*<<< orphan*/ * head; } ;
struct sir_dev {TYPE_2__ rx_buff; TYPE_1__ tx_buff; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree_skb (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sirdev_free_buffers(struct sir_dev *dev)
{
	kfree_skb(dev->rx_buff.skb);
	kfree(dev->tx_buff.head);
	dev->rx_buff.head = dev->tx_buff.head = NULL;
	dev->rx_buff.skb = NULL;
}