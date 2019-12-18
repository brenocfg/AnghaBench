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

/* Variables and functions */
 unsigned int AF_MAX ; 
 int /*<<< orphan*/  nf_conntrack_l3proto_generic ; 
 int /*<<< orphan*/  nf_conntrack_l4proto_generic ; 
 int /*<<< orphan*/ * nf_ct_l3protos ; 
 int nf_ct_l4proto_register_sysctl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int nf_conntrack_proto_init(void)
{
	unsigned int i;
	int err;

	err = nf_ct_l4proto_register_sysctl(&nf_conntrack_l4proto_generic);
	if (err < 0)
		return err;

	for (i = 0; i < AF_MAX; i++)
		rcu_assign_pointer(nf_ct_l3protos[i],
				   &nf_conntrack_l3proto_generic);
	return 0;
}