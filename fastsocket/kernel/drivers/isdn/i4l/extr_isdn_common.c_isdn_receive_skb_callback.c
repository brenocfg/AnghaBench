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
struct sk_buff {scalar_t__ len; } ;
struct TYPE_4__ {TYPE_1__** drv; int /*<<< orphan*/ * v110use; scalar_t__* v110; int /*<<< orphan*/ * ibytes; } ;
struct TYPE_3__ {int /*<<< orphan*/ * rcv_waitq; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 TYPE_2__* dev ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int isdn_dc2minor (int,int) ; 
 scalar_t__ isdn_net_rcv_skb (int,struct sk_buff*) ; 
 scalar_t__ isdn_tty_rcv_skb (int,int,int,struct sk_buff*) ; 
 struct sk_buff* isdn_v110_decode (scalar_t__,struct sk_buff*) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
isdn_receive_skb_callback(int di, int channel, struct sk_buff *skb)
{
	int i;

	if ((i = isdn_dc2minor(di, channel)) == -1) {
		dev_kfree_skb(skb);
		return;
	}
	/* Update statistics */
	dev->ibytes[i] += skb->len;
	
	/* First, try to deliver data to network-device */
	if (isdn_net_rcv_skb(i, skb))
		return;

	/* V.110 handling
	 * makes sense for async streams only, so it is
	 * called after possible net-device delivery.
	 */
	if (dev->v110[i]) {
		atomic_inc(&dev->v110use[i]);
		skb = isdn_v110_decode(dev->v110[i], skb);
		atomic_dec(&dev->v110use[i]);
		if (!skb)
			return;
	}

	/* No network-device found, deliver to tty or raw-channel */
	if (skb->len) {
		if (isdn_tty_rcv_skb(i, di, channel, skb))
			return;
		wake_up_interruptible(&dev->drv[di]->rcv_waitq[channel]);
	} else
		dev_kfree_skb(skb);
}