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
struct TYPE_2__ {int /*<<< orphan*/  ee_origin; int /*<<< orphan*/  ee_errno; } ;
struct sock_exterr_skb {TYPE_1__ ee; } ;
struct sock {int dummy; } ;
struct skb_shared_hwtstamps {int dummy; } ;
struct sk_buff {int /*<<< orphan*/  tstamp; struct sock* sk; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMSG ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 struct sock_exterr_skb* SKB_EXT_ERR (struct sk_buff*) ; 
 int /*<<< orphan*/  SO_EE_ORIGIN_TIMESTAMPING ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  ktime_get_real () ; 
 int /*<<< orphan*/  memset (struct sock_exterr_skb*,int /*<<< orphan*/ ,int) ; 
 struct sk_buff* skb_clone (struct sk_buff*,int /*<<< orphan*/ ) ; 
 struct skb_shared_hwtstamps* skb_hwtstamps (struct sk_buff*) ; 
 int sock_queue_err_skb (struct sock*,struct sk_buff*) ; 

void skb_tstamp_tx(struct sk_buff *orig_skb,
		struct skb_shared_hwtstamps *hwtstamps)
{
	struct sock *sk = orig_skb->sk;
	struct sock_exterr_skb *serr;
	struct sk_buff *skb;
	int err;

	if (!sk)
		return;

	skb = skb_clone(orig_skb, GFP_ATOMIC);
	if (!skb)
		return;

	if (hwtstamps) {
		*skb_hwtstamps(skb) =
			*hwtstamps;
	} else {
		/*
		 * no hardware time stamps available,
		 * so keep the skb_shared_tx and only
		 * store software time stamp
		 */
		skb->tstamp = ktime_get_real();
	}

	serr = SKB_EXT_ERR(skb);
	memset(serr, 0, sizeof(*serr));
	serr->ee.ee_errno = ENOMSG;
	serr->ee.ee_origin = SO_EE_ORIGIN_TIMESTAMPING;
	err = sock_queue_err_skb(sk, skb);
	if (err)
		kfree_skb(skb);
}