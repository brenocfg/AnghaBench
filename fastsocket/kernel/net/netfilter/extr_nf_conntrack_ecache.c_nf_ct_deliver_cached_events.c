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
struct nf_ct_event_notifier {int (* fcn ) (unsigned long,struct nf_ct_event*) ;} ;
struct nf_ct_event {int /*<<< orphan*/  report; int /*<<< orphan*/  pid; struct nf_conn* ct; } ;
struct nf_conntrack_ecache {unsigned long missed; int /*<<< orphan*/  cache; } ;
struct nf_conn {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  nf_conntrack_event_cb ; 
 struct nf_conntrack_ecache* nf_ct_ecache_find (struct nf_conn*) ; 
 scalar_t__ nf_ct_is_confirmed (struct nf_conn*) ; 
 int /*<<< orphan*/  nf_ct_is_dying (struct nf_conn*) ; 
 struct nf_ct_event_notifier* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int stub1 (unsigned long,struct nf_ct_event*) ; 
 scalar_t__ unlikely (int) ; 
 unsigned long xchg (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void nf_ct_deliver_cached_events(struct nf_conn *ct)
{
	unsigned long events;
	struct nf_ct_event_notifier *notify;
	struct nf_conntrack_ecache *e;

	rcu_read_lock();
	notify = rcu_dereference(nf_conntrack_event_cb);
	if (notify == NULL)
		goto out_unlock;

	e = nf_ct_ecache_find(ct);
	if (e == NULL)
		goto out_unlock;

	events = xchg(&e->cache, 0);

	if (nf_ct_is_confirmed(ct) && !nf_ct_is_dying(ct) && events) {
		struct nf_ct_event item = {
			.ct	= ct,
			.pid	= 0,
			.report	= 0
		};
		int ret;
		/* We make a copy of the missed event cache without taking
		 * the lock, thus we may send missed events twice. However,
		 * this does not harm and it happens very rarely. */
		unsigned long missed = e->missed;

		ret = notify->fcn(events | missed, &item);
		if (unlikely(ret < 0 || missed)) {
			spin_lock_bh(&ct->lock);
			if (ret < 0)
				e->missed |= events;
			else
				e->missed &= ~missed;
			spin_unlock_bh(&ct->lock);
		} 
	}

out_unlock:
	rcu_read_unlock();
}