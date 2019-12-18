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
 unsigned int PF_MAX ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nf_conntrack_l4proto_generic ; 
 int /*<<< orphan*/  nf_ct_l4proto_unregister_sysctl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * nf_ct_protos ; 

void nf_conntrack_proto_fini(void)
{
	unsigned int i;

	nf_ct_l4proto_unregister_sysctl(&nf_conntrack_l4proto_generic);

	/* free l3proto protocol tables */
	for (i = 0; i < PF_MAX; i++)
		kfree(nf_ct_protos[i]);
}