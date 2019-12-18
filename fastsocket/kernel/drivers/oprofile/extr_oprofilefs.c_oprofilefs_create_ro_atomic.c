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
struct super_block {int dummy; } ;
struct dentry {int dummy; } ;
typedef  int /*<<< orphan*/  atomic_t ;

/* Variables and functions */
 int __oprofilefs_create_file (struct super_block*,struct dentry*,char const*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_ro_fops ; 

int oprofilefs_create_ro_atomic(struct super_block *sb, struct dentry *root,
	char const *name, atomic_t *val)
{
	return __oprofilefs_create_file(sb, root, name,
					&atomic_ro_fops, 0444, val);
}