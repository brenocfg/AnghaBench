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
struct nf_conntrack_l4proto {int /*<<< orphan*/  ctl_compat_table; int /*<<< orphan*/ * ctl_compat_table_header; int /*<<< orphan*/ * ctl_table_users; int /*<<< orphan*/  ctl_table; int /*<<< orphan*/ ** ctl_table_header; } ;

/* Variables and functions */
 int /*<<< orphan*/  nf_ct_unregister_sysctl (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nf_ct_l4proto_unregister_sysctl(struct nf_conntrack_l4proto *l4proto)
{
#ifdef CONFIG_SYSCTL
	if (l4proto->ctl_table_header != NULL &&
	    *l4proto->ctl_table_header != NULL)
		nf_ct_unregister_sysctl(l4proto->ctl_table_header,
					l4proto->ctl_table,
					l4proto->ctl_table_users);
#ifdef CONFIG_NF_CONNTRACK_PROC_COMPAT
	if (l4proto->ctl_compat_table_header != NULL)
		nf_ct_unregister_sysctl(&l4proto->ctl_compat_table_header,
					l4proto->ctl_compat_table, NULL);
#endif /* CONFIG_NF_CONNTRACK_PROC_COMPAT */
#endif /* CONFIG_SYSCTL */
}