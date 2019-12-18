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
typedef  int u8 ;
typedef  int u32 ;
struct sk_buff {int dummy; } ;
struct net_device {int /*<<< orphan*/  addr_len; } ;
struct neighbour {int nud_state; int* ha; int flags; int /*<<< orphan*/  lock; int /*<<< orphan*/  arp_queue; int /*<<< orphan*/  (* output ) (struct sk_buff*) ;TYPE_1__* parms; void* confirmed; void* updated; struct net_device* dev; } ;
struct TYPE_4__ {struct neighbour* neighbour; } ;
struct TYPE_3__ {int base_reachable_time; int /*<<< orphan*/  reachable_time; } ;

/* Variables and functions */
 int EINVAL ; 
 int EPERM ; 
 int NEIGH_UPDATE_F_ADMIN ; 
 int NEIGH_UPDATE_F_ISROUTER ; 
 int NEIGH_UPDATE_F_OVERRIDE ; 
 int NEIGH_UPDATE_F_OVERRIDE_ISROUTER ; 
 int NEIGH_UPDATE_F_WEAK_OVERRIDE ; 
 int NTF_ROUTER ; 
 int NUD_CONNECTED ; 
 int NUD_FAILED ; 
 int NUD_INCOMPLETE ; 
 int NUD_IN_TIMER ; 
 int NUD_NOARP ; 
 int NUD_PERMANENT ; 
 int NUD_PROBE ; 
 int NUD_REACHABLE ; 
 int NUD_STALE ; 
 int NUD_VALID ; 
 struct sk_buff* __skb_dequeue (int /*<<< orphan*/ *) ; 
 void* jiffies ; 
 int /*<<< orphan*/  memcmp (int const*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int const**,int const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  neigh_add_timer (struct neighbour*,void*) ; 
 int /*<<< orphan*/  neigh_connect (struct neighbour*) ; 
 int /*<<< orphan*/  neigh_del_timer (struct neighbour*) ; 
 int /*<<< orphan*/  neigh_invalidate (struct neighbour*) ; 
 int /*<<< orphan*/  neigh_suspect (struct neighbour*) ; 
 int /*<<< orphan*/  neigh_update_hhs (struct neighbour*) ; 
 int /*<<< orphan*/  neigh_update_notify (struct neighbour*) ; 
 TYPE_2__* skb_dst (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_queue_purge (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct sk_buff*) ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

int neigh_update(struct neighbour *neigh, const u8 *lladdr, u8 new,
		 u32 flags)
{
	u8 old;
	int err;
	int notify = 0;
	struct net_device *dev;
	int update_isrouter = 0;

	write_lock_bh(&neigh->lock);

	dev    = neigh->dev;
	old    = neigh->nud_state;
	err    = -EPERM;

	if (!(flags & NEIGH_UPDATE_F_ADMIN) &&
	    (old & (NUD_NOARP | NUD_PERMANENT)))
		goto out;

	if (!(new & NUD_VALID)) {
		neigh_del_timer(neigh);
		if (old & NUD_CONNECTED)
			neigh_suspect(neigh);
		neigh->nud_state = new;
		err = 0;
		notify = old & NUD_VALID;
		if ((old & (NUD_INCOMPLETE | NUD_PROBE)) &&
		    (new & NUD_FAILED)) {
			neigh_invalidate(neigh);
			notify = 1;
		}
		goto out;
	}

	/* Compare new lladdr with cached one */
	if (!dev->addr_len) {
		/* First case: device needs no address. */
		lladdr = neigh->ha;
	} else if (lladdr) {
		/* The second case: if something is already cached
		   and a new address is proposed:
		   - compare new & old
		   - if they are different, check override flag
		 */
		if ((old & NUD_VALID) &&
		    !memcmp(lladdr, neigh->ha, dev->addr_len))
			lladdr = neigh->ha;
	} else {
		/* No address is supplied; if we know something,
		   use it, otherwise discard the request.
		 */
		err = -EINVAL;
		if (!(old & NUD_VALID))
			goto out;
		lladdr = neigh->ha;
	}

	if (new & NUD_CONNECTED)
		neigh->confirmed = jiffies;
	neigh->updated = jiffies;

	/* If entry was valid and address is not changed,
	   do not change entry state, if new one is STALE.
	 */
	err = 0;
	update_isrouter = flags & NEIGH_UPDATE_F_OVERRIDE_ISROUTER;
	if (old & NUD_VALID) {
		if (lladdr != neigh->ha && !(flags & NEIGH_UPDATE_F_OVERRIDE)) {
			update_isrouter = 0;
			if ((flags & NEIGH_UPDATE_F_WEAK_OVERRIDE) &&
			    (old & NUD_CONNECTED)) {
				lladdr = neigh->ha;
				new = NUD_STALE;
			} else
				goto out;
		} else {
			if (lladdr == neigh->ha && new == NUD_STALE &&
			    ((flags & NEIGH_UPDATE_F_WEAK_OVERRIDE) ||
			     (old & NUD_CONNECTED))
			    )
				new = old;
		}
	}

	if (new != old) {
		neigh_del_timer(neigh);
		if (new & NUD_IN_TIMER)
			neigh_add_timer(neigh, (jiffies +
						((new & NUD_REACHABLE) ?
						 neigh->parms->reachable_time :
						 0)));
		neigh->nud_state = new;
	}

	if (lladdr != neigh->ha) {
		memcpy(&neigh->ha, lladdr, dev->addr_len);
		neigh_update_hhs(neigh);
		if (!(new & NUD_CONNECTED))
			neigh->confirmed = jiffies -
				      (neigh->parms->base_reachable_time << 1);
		notify = 1;
	}
	if (new == old)
		goto out;
	if (new & NUD_CONNECTED)
		neigh_connect(neigh);
	else
		neigh_suspect(neigh);
	if (!(old & NUD_VALID)) {
		struct sk_buff *skb;

		/* Again: avoid dead loop if something went wrong */

		while (neigh->nud_state & NUD_VALID &&
		       (skb = __skb_dequeue(&neigh->arp_queue)) != NULL) {
			struct neighbour *n1 = neigh;
			write_unlock_bh(&neigh->lock);
			/* On shaper/eql skb->dst->neighbour != neigh :( */
			if (skb_dst(skb) && skb_dst(skb)->neighbour)
				n1 = skb_dst(skb)->neighbour;
			n1->output(skb);
			write_lock_bh(&neigh->lock);
		}
		skb_queue_purge(&neigh->arp_queue);
	}
out:
	if (update_isrouter) {
		neigh->flags = (flags & NEIGH_UPDATE_F_ISROUTER) ?
			(neigh->flags | NTF_ROUTER) :
			(neigh->flags & ~NTF_ROUTER);
	}
	write_unlock_bh(&neigh->lock);

	if (notify)
		neigh_update_notify(neigh);

	return err;
}