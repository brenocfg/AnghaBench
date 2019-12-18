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
struct nf_conn {int dummy; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NF_CT_STAT_INC (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clean_from_lists (struct nf_conn*) ; 
 int /*<<< orphan*/  delete_list ; 
 int /*<<< orphan*/  nf_conntrack_lock ; 
 int /*<<< orphan*/  nf_ct_helper_destroy (struct nf_conn*) ; 
 struct net* nf_ct_net (struct nf_conn*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

void nf_ct_delete_from_lists(struct nf_conn *ct)
{
	struct net *net = nf_ct_net(ct);

	nf_ct_helper_destroy(ct);
	spin_lock_bh(&nf_conntrack_lock);
	/* Inside lock so preempt is disabled on module removal path.
	 * Otherwise we can get spurious warnings. */
	NF_CT_STAT_INC(net, delete_list);
	clean_from_lists(ct);
	spin_unlock_bh(&nf_conntrack_lock);
}