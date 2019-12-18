#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ expires; } ;
struct nf_conn {TYPE_3__ timeout; TYPE_1__* tuplehash; } ;
struct TYPE_6__ {int sysctl_events_retry_timeout; int /*<<< orphan*/  dying; } ;
struct net {TYPE_2__ ct; } ;
struct TYPE_5__ {int /*<<< orphan*/  hnnode; } ;

/* Variables and functions */
 size_t IP_CT_DIR_ORIGINAL ; 
 int /*<<< orphan*/  add_timer (TYPE_3__*) ; 
 int /*<<< orphan*/  death_by_event ; 
 int /*<<< orphan*/  hlist_nulls_add_head (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  nf_conntrack_lock ; 
 struct net* nf_ct_net (struct nf_conn*) ; 
 int random32 () ; 
 int /*<<< orphan*/  setup_timer (TYPE_3__*,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

void nf_ct_insert_dying_list(struct nf_conn *ct)
{
	struct net *net = nf_ct_net(ct);

	/* add this conntrack to the dying list */
	spin_lock_bh(&nf_conntrack_lock);
	hlist_nulls_add_head(&ct->tuplehash[IP_CT_DIR_ORIGINAL].hnnode,
			     &net->ct.dying);
	spin_unlock_bh(&nf_conntrack_lock);
	/* set a new timer to retry event delivery */
	setup_timer(&ct->timeout, death_by_event, (unsigned long)ct);
	ct->timeout.expires = jiffies +
		(random32() % net->ct.sysctl_events_retry_timeout);
	add_timer(&ct->timeout);
}