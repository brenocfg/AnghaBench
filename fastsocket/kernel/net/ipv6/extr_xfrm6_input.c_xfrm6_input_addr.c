#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xfrm_address_t ;
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_8__ {int /*<<< orphan*/  packets; int /*<<< orphan*/  bytes; } ;
struct TYPE_6__ {scalar_t__ state; } ;
struct TYPE_5__ {int flags; } ;
struct xfrm_state {int /*<<< orphan*/  lock; TYPE_4__ curlft; TYPE_3__* type; TYPE_2__ km; TYPE_1__ props; } ;
struct sk_buff {scalar_t__ len; struct sec_path* sp; int /*<<< orphan*/  mark; int /*<<< orphan*/  dev; } ;
struct sec_path {scalar_t__ len; struct xfrm_state** xvec; int /*<<< orphan*/  refcnt; } ;
struct net {int dummy; } ;
struct TYPE_7__ {scalar_t__ (* input ) (struct xfrm_state*,struct sk_buff*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET6 ; 
 int /*<<< orphan*/  LINUX_MIB_XFRMINBUFFERERROR ; 
 int /*<<< orphan*/  LINUX_MIB_XFRMINERROR ; 
 int /*<<< orphan*/  LINUX_MIB_XFRMINNOSTATES ; 
 int /*<<< orphan*/  XFRM_INC_STATS (struct net*,int /*<<< orphan*/ ) ; 
 scalar_t__ XFRM_MAX_DEPTH ; 
 scalar_t__ XFRM_STATE_VALID ; 
 int XFRM_STATE_WILDRECV ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 struct net* dev_net (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  in6addr_any ; 
 scalar_t__ likely (int) ; 
 struct sec_path* secpath_dup (struct sec_path*) ; 
 int /*<<< orphan*/  secpath_put (struct sec_path*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ stub1 (struct xfrm_state*,struct sk_buff*) ; 
 int /*<<< orphan*/  xfrm_audit_state_notfound_simple (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfrm_state_check_expire (struct xfrm_state*) ; 
 struct xfrm_state* xfrm_state_lookup_byaddr (struct net*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfrm_state_put (struct xfrm_state*) ; 

int xfrm6_input_addr(struct sk_buff *skb, xfrm_address_t *daddr,
		     xfrm_address_t *saddr, u8 proto)
{
	struct net *net = dev_net(skb->dev);
	struct xfrm_state *x = NULL;
	int i = 0;

	/* Allocate new secpath or COW existing one. */
	if (!skb->sp || atomic_read(&skb->sp->refcnt) != 1) {
		struct sec_path *sp;

		sp = secpath_dup(skb->sp);
		if (!sp) {
			XFRM_INC_STATS(net, LINUX_MIB_XFRMINERROR);
			goto drop;
		}
		if (skb->sp)
			secpath_put(skb->sp);
		skb->sp = sp;
	}

	if (1 + skb->sp->len == XFRM_MAX_DEPTH) {
		XFRM_INC_STATS(net, LINUX_MIB_XFRMINBUFFERERROR);
		goto drop;
	}

	for (i = 0; i < 3; i++) {
		xfrm_address_t *dst, *src;

		switch (i) {
		case 0:
			dst = daddr;
			src = saddr;
			break;
		case 1:
			/* lookup state with wild-card source address */
			dst = daddr;
			src = (xfrm_address_t *)&in6addr_any;
			break;
		default:
			/* lookup state with wild-card addresses */
			dst = (xfrm_address_t *)&in6addr_any;
			src = (xfrm_address_t *)&in6addr_any;
			break;
		}

		x = xfrm_state_lookup_byaddr(net, skb->mark, dst, src, proto, AF_INET6);
		if (!x)
			continue;

		spin_lock(&x->lock);

		if ((!i || (x->props.flags & XFRM_STATE_WILDRECV)) &&
		    likely(x->km.state == XFRM_STATE_VALID) &&
		    !xfrm_state_check_expire(x)) {
			spin_unlock(&x->lock);
			if (x->type->input(x, skb) > 0) {
				/* found a valid state */
				break;
			}
		} else
			spin_unlock(&x->lock);

		xfrm_state_put(x);
		x = NULL;
	}

	if (!x) {
		XFRM_INC_STATS(net, LINUX_MIB_XFRMINNOSTATES);
		xfrm_audit_state_notfound_simple(skb, AF_INET6);
		goto drop;
	}

	skb->sp->xvec[skb->sp->len++] = x;

	spin_lock(&x->lock);

	x->curlft.bytes += skb->len;
	x->curlft.packets++;

	spin_unlock(&x->lock);

	return 1;

drop:
	return -1;
}