#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  packets; int /*<<< orphan*/  bytes; } ;
struct TYPE_9__ {scalar_t__ oseq; } ;
struct xfrm_state {int /*<<< orphan*/  lock; TYPE_5__* type; TYPE_4__ curlft; TYPE_3__ replay; TYPE_1__* outer_mode; } ;
struct sk_buff {scalar_t__ len; } ;
struct net {int dummy; } ;
struct dst_entry {struct xfrm_state* xfrm; } ;
struct TYPE_8__ {scalar_t__ output; } ;
struct TYPE_12__ {TYPE_2__ seq; } ;
struct TYPE_11__ {int flags; int (* output ) (struct xfrm_state*,struct sk_buff*) ;} ;
struct TYPE_7__ {int flags; int (* output ) (struct xfrm_state*,struct sk_buff*) ;} ;

/* Variables and functions */
 int EHOSTUNREACH ; 
 int EINPROGRESS ; 
 int EOVERFLOW ; 
 int /*<<< orphan*/  LINUX_MIB_XFRMOUTERROR ; 
 int /*<<< orphan*/  LINUX_MIB_XFRMOUTSTATEEXPIRED ; 
 int /*<<< orphan*/  LINUX_MIB_XFRMOUTSTATEMODEERROR ; 
 int /*<<< orphan*/  LINUX_MIB_XFRMOUTSTATEPROTOERROR ; 
 int /*<<< orphan*/  LINUX_MIB_XFRMOUTSTATESEQERROR ; 
 int /*<<< orphan*/  XFRM_INC_STATS (struct net*,int /*<<< orphan*/ ) ; 
 int XFRM_MODE_FLAG_TUNNEL ; 
 int /*<<< orphan*/  XFRM_REPLAY_UPDATE ; 
 TYPE_6__* XFRM_SKB_CB (struct sk_buff*) ; 
 int XFRM_TYPE_REPLAY_PROT ; 
 struct dst_entry* dst_pop (struct dst_entry*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 struct dst_entry* skb_dst (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_dst_set (struct sk_buff*,struct dst_entry*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int stub1 (struct xfrm_state*,struct sk_buff*) ; 
 int stub2 (struct xfrm_state*,struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 
 scalar_t__ xfrm_aevent_is_on (struct net*) ; 
 int /*<<< orphan*/  xfrm_audit_state_replay_overflow (struct xfrm_state*,struct sk_buff*) ; 
 int /*<<< orphan*/  xfrm_replay_notify (struct xfrm_state*,int /*<<< orphan*/ ) ; 
 int xfrm_state_check_expire (struct xfrm_state*) ; 
 int xfrm_state_check_space (struct xfrm_state*,struct sk_buff*) ; 
 struct net* xs_net (struct xfrm_state*) ; 

__attribute__((used)) static int xfrm_output_one(struct sk_buff *skb, int err)
{
	struct dst_entry *dst = skb_dst(skb);
	struct xfrm_state *x = dst->xfrm;
	struct net *net = xs_net(x);

	if (err <= 0)
		goto resume;

	do {
		err = xfrm_state_check_space(x, skb);
		if (err) {
			XFRM_INC_STATS(net, LINUX_MIB_XFRMOUTERROR);
			goto error_nolock;
		}

		err = x->outer_mode->output(x, skb);
		if (err) {
			XFRM_INC_STATS(net, LINUX_MIB_XFRMOUTSTATEMODEERROR);
			goto error_nolock;
		}

		spin_lock_bh(&x->lock);
		err = xfrm_state_check_expire(x);
		if (err) {
			XFRM_INC_STATS(net, LINUX_MIB_XFRMOUTSTATEEXPIRED);
			goto error;
		}

		if (x->type->flags & XFRM_TYPE_REPLAY_PROT) {
			XFRM_SKB_CB(skb)->seq.output = ++x->replay.oseq;
			if (unlikely(x->replay.oseq == 0)) {
				XFRM_INC_STATS(net, LINUX_MIB_XFRMOUTSTATESEQERROR);
				x->replay.oseq--;
				xfrm_audit_state_replay_overflow(x, skb);
				err = -EOVERFLOW;
				goto error;
			}
			if (xfrm_aevent_is_on(net))
				xfrm_replay_notify(x, XFRM_REPLAY_UPDATE);
		}

		x->curlft.bytes += skb->len;
		x->curlft.packets++;

		spin_unlock_bh(&x->lock);

		err = x->type->output(x, skb);
		if (err == -EINPROGRESS)
			goto out_exit;

resume:
		if (err) {
			XFRM_INC_STATS(net, LINUX_MIB_XFRMOUTSTATEPROTOERROR);
			goto error_nolock;
		}

		dst = dst_pop(dst);
		if (!dst) {
			XFRM_INC_STATS(net, LINUX_MIB_XFRMOUTERROR);
			err = -EHOSTUNREACH;
			goto error_nolock;
		}
		skb_dst_set(skb, dst);
		x = dst->xfrm;
	} while (x && !(x->outer_mode->flags & XFRM_MODE_FLAG_TUNNEL));

	err = 0;

out_exit:
	return err;
error:
	spin_unlock_bh(&x->lock);
error_nolock:
	kfree_skb(skb);
	goto out_exit;
}