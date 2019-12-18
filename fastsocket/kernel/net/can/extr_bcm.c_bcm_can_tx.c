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
struct sk_buff {int /*<<< orphan*/  sk; struct net_device* dev; } ;
struct net_device {int dummy; } ;
struct can_frame {int dummy; } ;
struct bcm_op {size_t currframe; size_t nframes; int /*<<< orphan*/  frames_abs; int /*<<< orphan*/  sk; int /*<<< orphan*/  ifindex; struct can_frame* frames; } ;

/* Variables and functions */
 int /*<<< orphan*/  CFSIZ ; 
 struct sk_buff* alloc_skb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  can_send (struct sk_buff*,int) ; 
 struct net_device* dev_get_by_index (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_put (struct net_device*) ; 
 int /*<<< orphan*/  gfp_any () ; 
 int /*<<< orphan*/  init_net ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,struct can_frame*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bcm_can_tx(struct bcm_op *op)
{
	struct sk_buff *skb;
	struct net_device *dev;
	struct can_frame *cf = &op->frames[op->currframe];

	/* no target device? => exit */
	if (!op->ifindex)
		return;

	dev = dev_get_by_index(&init_net, op->ifindex);
	if (!dev) {
		/* RFC: should this bcm_op remove itself here? */
		return;
	}

	skb = alloc_skb(CFSIZ, gfp_any());
	if (!skb)
		goto out;

	memcpy(skb_put(skb, CFSIZ), cf, CFSIZ);

	/* send with loopback */
	skb->dev = dev;
	skb->sk = op->sk;
	can_send(skb, 1);

	/* update statistics */
	op->currframe++;
	op->frames_abs++;

	/* reached last frame? */
	if (op->currframe >= op->nframes)
		op->currframe = 0;
 out:
	dev_put(dev);
}