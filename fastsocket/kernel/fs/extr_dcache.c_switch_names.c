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
struct TYPE_2__ {scalar_t__ len; scalar_t__ name; } ;
struct dentry {TYPE_1__ d_name; scalar_t__ d_iname; } ;

/* Variables and functions */
 scalar_t__ dname_external (struct dentry*) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  swap (scalar_t__,scalar_t__) ; 

__attribute__((used)) static void switch_names(struct dentry *dentry, struct dentry *target)
{
	if (dname_external(target)) {
		if (dname_external(dentry)) {
			/*
			 * Both external: swap the pointers
			 */
			swap(target->d_name.name, dentry->d_name.name);
		} else {
			/*
			 * dentry:internal, target:external.  Steal target's
			 * storage and make target internal.
			 */
			memcpy(target->d_iname, dentry->d_name.name,
					dentry->d_name.len + 1);
			dentry->d_name.name = target->d_name.name;
			target->d_name.name = target->d_iname;
		}
	} else {
		if (dname_external(dentry)) {
			/*
			 * dentry:external, target:internal.  Give dentry's
			 * storage to target and make dentry internal
			 */
			memcpy(dentry->d_iname, target->d_name.name,
					target->d_name.len + 1);
			target->d_name.name = dentry->d_name.name;
			dentry->d_name.name = dentry->d_iname;
		} else {
			/*
			 * Both are internal.  Just copy target to dentry
			 */
			memcpy(dentry->d_iname, target->d_name.name,
					target->d_name.len + 1);
			dentry->d_name.len = target->d_name.len;
			return;
		}
	}
	swap(dentry->d_name.len, target->d_name.len);
}