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
struct nsproxy {struct net* net_ns; } ;
struct net {int dummy; } ;
struct ctl_table_header {int dummy; } ;
struct ctl_table {int dummy; } ;
struct ctl_path {int dummy; } ;
struct TYPE_2__ {struct nsproxy* nsproxy; } ;

/* Variables and functions */
 struct ctl_table_header* __register_sysctl_paths (int /*<<< orphan*/ *,struct nsproxy*,struct ctl_path const*,struct ctl_table*) ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  net_sysctl_root ; 

struct ctl_table_header *register_net_sysctl_table(struct net *net,
	const struct ctl_path *path, struct ctl_table *table)
{
	struct nsproxy namespaces;
	namespaces = *current->nsproxy;
	namespaces.net_ns = net;
	return __register_sysctl_paths(&net_sysctl_root,
					&namespaces, path, table);
}