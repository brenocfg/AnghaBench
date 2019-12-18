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
struct trans_ctl_table {scalar_t__ ctl_name; struct trans_ctl_table* child; scalar_t__ procname; } ;
struct ctl_table {scalar_t__ ctl_name; scalar_t__ procname; } ;

/* Variables and functions */
 scalar_t__ strcmp (scalar_t__,scalar_t__) ; 
 int sysctl_depth (struct ctl_table*) ; 
 struct ctl_table* sysctl_parent (struct ctl_table*,int) ; 
 struct trans_ctl_table* trans_root_table ; 

__attribute__((used)) static const struct trans_ctl_table *sysctl_binary_lookup(struct ctl_table *table)
{
	struct ctl_table *test;
	const struct trans_ctl_table *ref;
	int cur_depth;

	cur_depth = sysctl_depth(table);

	ref = trans_root_table;
repeat:
	test = sysctl_parent(table, cur_depth);
	for (; ref->ctl_name || ref->procname || ref->child; ref++) {
		int match = 0;

		if (cur_depth && !ref->child)
			continue;

		if (test->procname && ref->procname &&
			(strcmp(test->procname, ref->procname) == 0))
			match++;

		if (test->ctl_name && ref->ctl_name &&
			(test->ctl_name == ref->ctl_name))
			match++;

		if (!ref->ctl_name && !ref->procname)
			match++;

		if (match) {
			if (cur_depth != 0) {
				cur_depth--;
				ref = ref->child;
				goto repeat;
			}
			goto out;
		}
	}
	ref = NULL;
out:
	return ref;
}