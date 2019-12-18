#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct x25_neigh {TYPE_1__* dev; } ;
struct sk_buff {TYPE_1__* dev; int /*<<< orphan*/  protocol; } ;
struct TYPE_2__ {int type; } ;

/* Variables and functions */
#define  ARPHRD_ETHER 129 
#define  ARPHRD_X25 128 
 int /*<<< orphan*/  ETH_P_X25 ; 
 int /*<<< orphan*/  dev_queue_xmit (struct sk_buff*) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 unsigned char* skb_push (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_reset_network_header (struct sk_buff*) ; 

void x25_send_frame(struct sk_buff *skb, struct x25_neigh *nb)
{
	unsigned char *dptr;

	skb_reset_network_header(skb);

	switch (nb->dev->type) {
		case ARPHRD_X25:
			dptr  = skb_push(skb, 1);
			*dptr = 0x00;
			break;

#if defined(CONFIG_LLC) || defined(CONFIG_LLC_MODULE)
		case ARPHRD_ETHER:
			kfree_skb(skb);
			return;
#endif
		default:
			kfree_skb(skb);
			return;
	}

	skb->protocol = htons(ETH_P_X25);
	skb->dev      = nb->dev;

	dev_queue_xmit(skb);
}