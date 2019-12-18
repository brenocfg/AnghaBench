#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ expires; } ;
struct nf_conn {TYPE_2__* tuplehash; int /*<<< orphan*/  status; TYPE_3__ timeout; } ;
struct TYPE_4__ {int sysctl_events_retry_timeout; } ;
struct net {TYPE_1__ ct; } ;
struct TYPE_5__ {int /*<<< orphan*/  hnnode; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPCT_DESTROY ; 
 int /*<<< orphan*/  IPS_DYING_BIT ; 
 size_t IP_CT_DIR_ORIGINAL ; 
 int /*<<< orphan*/  add_timer (TYPE_3__*) ; 
 int /*<<< orphan*/  hlist_nulls_del (int /*<<< orphan*/ *) ; 
 scalar_t__ jiffies ; 
 scalar_t__ nf_conntrack_event (int /*<<< orphan*/ ,struct nf_conn*) ; 
 int /*<<< orphan*/  nf_conntrack_lock ; 
 struct net* nf_ct_net (struct nf_conn*) ; 
 int /*<<< orphan*/  nf_ct_put (struct nf_conn*) ; 
 int random32 () ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void death_by_event(unsigned long ul_conntrack)
{
	struct nf_conn *ct = (void *)ul_conntrack;
	struct net *net = nf_ct_net(ct);

	if (nf_conntrack_event(IPCT_DESTROY, ct) < 0) {
		/* bad luck, let's retry again */
		ct->timeout.expires = jiffies +
			(random32() % net->ct.sysctl_events_retry_timeout);
		add_timer(&ct->timeout);
		return;
	}
	/* we've got the event delivered, now it's dying */
	set_bit(IPS_DYING_BIT, &ct->status);
	spin_lock(&nf_conntrack_lock);
	hlist_nulls_del(&ct->tuplehash[IP_CT_DIR_ORIGINAL].hnnode);
	spin_unlock(&nf_conntrack_lock);
	nf_ct_put(ct);
}