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
struct nf_conn_nat {int /*<<< orphan*/  bysource; TYPE_1__* ct; } ;
struct nf_conn {int dummy; } ;
struct TYPE_2__ {int status; } ;

/* Variables and functions */
 int IPS_SRC_NAT_DONE ; 
 int /*<<< orphan*/  NF_CT_ASSERT (int) ; 
 int /*<<< orphan*/  NF_CT_EXT_NAT ; 
 int /*<<< orphan*/  hlist_del_rcu (int /*<<< orphan*/ *) ; 
 struct nf_conn_nat* nf_ct_ext_find (struct nf_conn*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nf_nat_lock ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nf_nat_cleanup_conntrack(struct nf_conn *ct)
{
	struct nf_conn_nat *nat = nf_ct_ext_find(ct, NF_CT_EXT_NAT);

	if (nat == NULL || nat->ct == NULL)
		return;

	NF_CT_ASSERT(nat->ct->status & IPS_SRC_NAT_DONE);

	spin_lock_bh(&nf_nat_lock);
	hlist_del_rcu(&nat->bysource);
	spin_unlock_bh(&nf_nat_lock);
}