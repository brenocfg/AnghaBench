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
struct nsproxy {int dummy; } ;
struct ctl_table {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  set_fail (char const**,struct ctl_table*,char*) ; 
 struct ctl_table* sysctl_check_lookup (struct nsproxy*,struct ctl_table*) ; 

__attribute__((used)) static void sysctl_check_leaf(struct nsproxy *namespaces,
				struct ctl_table *table, const char **fail)
{
	struct ctl_table *ref;

	ref = sysctl_check_lookup(namespaces, table);
	if (ref && (ref != table))
		set_fail(fail, table, "Sysctl already exists");
}