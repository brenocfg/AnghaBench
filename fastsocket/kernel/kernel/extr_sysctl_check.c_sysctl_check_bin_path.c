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
struct trans_ctl_table {scalar_t__ ctl_name; scalar_t__ procname; } ;
struct ctl_table {scalar_t__ ctl_name; int /*<<< orphan*/  procname; } ;

/* Variables and functions */
 int /*<<< orphan*/  set_fail (char const**,struct ctl_table*,char*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,scalar_t__) ; 
 struct trans_ctl_table* sysctl_binary_lookup (struct ctl_table*) ; 

__attribute__((used)) static void sysctl_check_bin_path(struct ctl_table *table, const char **fail)
{
	const struct trans_ctl_table *ref;

	ref = sysctl_binary_lookup(table);
	if (table->ctl_name && !ref)
		set_fail(fail, table, "Unknown sysctl binary path");
	if (ref) {
		if (ref->procname &&
		    (!table->procname ||
		     (strcmp(table->procname, ref->procname) != 0)))
			set_fail(fail, table, "procname does not match binary path procname");

		if (ref->ctl_name && table->ctl_name &&
		    (table->ctl_name != ref->ctl_name))
			set_fail(fail, table, "ctl_name does not match binary path ctl_name");
	}
}