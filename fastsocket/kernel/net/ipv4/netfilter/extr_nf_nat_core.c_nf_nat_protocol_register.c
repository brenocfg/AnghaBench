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
 int EBUSY ; 
 int /*<<< orphan*/  nf_nat_lock ; 
 int /*<<< orphan*/ ** nf_nat_protos ; 
 int /*<<< orphan*/  nf_nat_unknown_protocol ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ *,struct nf_nat_protocol const*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

int nf_nat_protocol_register(const struct nf_nat_protocol *proto)
{
	int ret = 0;

	spin_lock_bh(&nf_nat_lock);
	if (nf_nat_protos[proto->protonum] != &nf_nat_unknown_protocol) {
		ret = -EBUSY;
		goto out;
	}
	rcu_assign_pointer(nf_nat_protos[proto->protonum], proto);
 out:
	spin_unlock_bh(&nf_nat_lock);
	return ret;
}