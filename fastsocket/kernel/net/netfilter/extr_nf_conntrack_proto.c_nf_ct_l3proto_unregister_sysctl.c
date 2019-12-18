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
struct nf_conntrack_l3proto {int /*<<< orphan*/  ctl_table; int /*<<< orphan*/ * ctl_table_header; } ;

/* Variables and functions */
 int /*<<< orphan*/  nf_ct_unregister_sysctl (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nf_ct_l3proto_unregister_sysctl(struct nf_conntrack_l3proto *l3proto)
{
#ifdef CONFIG_SYSCTL
	if (l3proto->ctl_table_header != NULL)
		nf_ct_unregister_sysctl(&l3proto->ctl_table_header,
					l3proto->ctl_table, NULL);
#endif
}