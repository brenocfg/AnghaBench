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
struct nsproxy {int /*<<< orphan*/  net_ns; } ;
struct ctl_table_root {int dummy; } ;
struct ctl_table {int mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  init_net ; 
 scalar_t__ net_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int net_ctl_ro_header_perms(struct ctl_table_root *root,
		struct nsproxy *namespaces, struct ctl_table *table)
{
	if (net_eq(namespaces->net_ns, &init_net))
		return table->mode;
	else
		return table->mode & ~0222;
}