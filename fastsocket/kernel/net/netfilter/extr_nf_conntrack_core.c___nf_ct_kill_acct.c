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
struct sk_buff {scalar_t__ len; } ;
struct nf_conn_counter {int /*<<< orphan*/  bytes; int /*<<< orphan*/  packets; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* function ) (unsigned long) ;} ;
struct nf_conn {TYPE_1__ timeout; int /*<<< orphan*/  lock; } ;
typedef  enum ip_conntrack_info { ____Placeholder_ip_conntrack_info } ip_conntrack_info ;

/* Variables and functions */
 size_t CTINFO2DIR (int) ; 
 scalar_t__ del_timer (TYPE_1__*) ; 
 struct nf_conn_counter* nf_conn_acct_find (struct nf_conn*) ; 
 scalar_t__ skb_network_offset (struct sk_buff const*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (unsigned long) ; 

bool __nf_ct_kill_acct(struct nf_conn *ct,
		       enum ip_conntrack_info ctinfo,
		       const struct sk_buff *skb,
		       int do_acct)
{
	if (do_acct) {
		struct nf_conn_counter *acct;

		acct = nf_conn_acct_find(ct);
		if (acct) {
			spin_lock_bh(&ct->lock);
			acct[CTINFO2DIR(ctinfo)].packets++;
			acct[CTINFO2DIR(ctinfo)].bytes +=
				skb->len - skb_network_offset(skb);
			spin_unlock_bh(&ct->lock);
		}
	}

	if (del_timer(&ct->timeout)) {
		ct->timeout.function((unsigned long)ct);
		return true;
	}
	return false;
}