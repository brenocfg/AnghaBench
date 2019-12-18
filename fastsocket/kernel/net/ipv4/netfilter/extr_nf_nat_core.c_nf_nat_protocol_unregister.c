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
struct nf_nat_protocol {size_t protonum; } ;

/* Variables and functions */
 int /*<<< orphan*/  nf_nat_lock ; 
 int /*<<< orphan*/ * nf_nat_protos ; 
 int /*<<< orphan*/  nf_nat_unknown_protocol ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  synchronize_rcu () ; 

void nf_nat_protocol_unregister(const struct nf_nat_protocol *proto)
{
	spin_lock_bh(&nf_nat_lock);
	rcu_assign_pointer(nf_nat_protos[proto->protonum],
			   &nf_nat_unknown_protocol);
	spin_unlock_bh(&nf_nat_lock);
	synchronize_rcu();
}