#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  state; int /*<<< orphan*/  in_frame; scalar_t__ len; int /*<<< orphan*/ * head; int /*<<< orphan*/ * data; TYPE_3__* skb; int /*<<< orphan*/  truesize; } ;
struct TYPE_6__ {scalar_t__ len; int /*<<< orphan*/ * head; int /*<<< orphan*/ * data; int /*<<< orphan*/  truesize; } ;
struct sir_dev {TYPE_2__ rx_buff; TYPE_1__ tx_buff; int /*<<< orphan*/  netdev; } ;
struct TYPE_8__ {int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IRDA_SKB_MAX_MTU ; 
 int /*<<< orphan*/  OUTSIDE_FRAME ; 
 int /*<<< orphan*/  SIRBUF_ALLOCSIZE ; 
 TYPE_3__* __netdev_alloc_skb (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_skb (TYPE_3__*) ; 
 int /*<<< orphan*/ * kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_reserve (TYPE_3__*,int) ; 

__attribute__((used)) static int sirdev_alloc_buffers(struct sir_dev *dev)
{
	dev->tx_buff.truesize = SIRBUF_ALLOCSIZE;
	dev->rx_buff.truesize = IRDA_SKB_MAX_MTU; 

	/* Bootstrap ZeroCopy Rx */
	dev->rx_buff.skb = __netdev_alloc_skb(dev->netdev, dev->rx_buff.truesize,
					      GFP_KERNEL);
	if (dev->rx_buff.skb == NULL)
		return -ENOMEM;
	skb_reserve(dev->rx_buff.skb, 1);
	dev->rx_buff.head = dev->rx_buff.skb->data;

	dev->tx_buff.head = kmalloc(dev->tx_buff.truesize, GFP_KERNEL);
	if (dev->tx_buff.head == NULL) {
		kfree_skb(dev->rx_buff.skb);
		dev->rx_buff.skb = NULL;
		dev->rx_buff.head = NULL;
		return -ENOMEM;
	}

	dev->tx_buff.data = dev->tx_buff.head;
	dev->rx_buff.data = dev->rx_buff.head;
	dev->tx_buff.len = 0;
	dev->rx_buff.len = 0;

	dev->rx_buff.in_frame = FALSE;
	dev->rx_buff.state = OUTSIDE_FRAME;
	return 0;
}