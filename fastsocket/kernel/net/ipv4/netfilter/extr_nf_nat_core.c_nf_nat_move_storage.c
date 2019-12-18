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
struct nf_conn_nat {int /*<<< orphan*/  bysource; struct nf_conn* ct; } ;
struct nf_conn {int status; } ;

/* Variables and functions */
 int IPS_SRC_NAT_DONE ; 
 int /*<<< orphan*/  hlist_replace_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nf_nat_lock ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nf_nat_move_storage(void *new, void *old)
{
	struct nf_conn_nat *new_nat = new;
	struct nf_conn_nat *old_nat = old;
	struct nf_conn *ct = old_nat->ct;

	if (!ct || !(ct->status & IPS_SRC_NAT_DONE))
		return;

	spin_lock_bh(&nf_nat_lock);
	hlist_replace_rcu(&old_nat->bysource, &new_nat->bysource);
	spin_unlock_bh(&nf_nat_lock);
}