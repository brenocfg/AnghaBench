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
struct ppp {TYPE_2__* dev; } ;
struct channel {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  rx_length_errors; } ;
struct TYPE_4__ {TYPE_1__ stats; } ;

/* Variables and functions */
 scalar_t__ PPP_MP ; 
 scalar_t__ PPP_PROTO (struct sk_buff*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  ppp_receive_error (struct ppp*) ; 
 int /*<<< orphan*/  ppp_receive_mp_frame (struct ppp*,struct sk_buff*,struct channel*) ; 
 int /*<<< orphan*/  ppp_receive_nonmp_frame (struct ppp*,struct sk_buff*) ; 
 scalar_t__ pskb_may_pull (struct sk_buff*,int) ; 

__attribute__((used)) static void
ppp_receive_frame(struct ppp *ppp, struct sk_buff *skb, struct channel *pch)
{
	if (pskb_may_pull(skb, 2)) {
#ifdef CONFIG_PPP_MULTILINK
		/* XXX do channel-level decompression here */
		if (PPP_PROTO(skb) == PPP_MP)
			ppp_receive_mp_frame(ppp, skb, pch);
		else
#endif /* CONFIG_PPP_MULTILINK */
			ppp_receive_nonmp_frame(ppp, skb);
		return;
	}

	if (skb->len > 0)
		/* note: a 0-length skb is used as an error indication */
		++ppp->dev->stats.rx_length_errors;

	kfree_skb(skb);
	ppp_receive_error(ppp);
}