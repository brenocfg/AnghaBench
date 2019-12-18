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
struct super_block {struct cgroupfs_root* s_fs_info; } ;
struct cgroupfs_root {scalar_t__ subsys_bits; int /*<<< orphan*/  name; } ;
struct cgroup_sb_opts {scalar_t__ subsys_bits; scalar_t__ none; scalar_t__ name; } ;

/* Variables and functions */
 scalar_t__ strcmp (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cgroup_test_super(struct super_block *sb, void *data)
{
	struct cgroup_sb_opts *opts = data;
	struct cgroupfs_root *root = sb->s_fs_info;

	/* If we asked for a name then it must match */
	if (opts->name && strcmp(opts->name, root->name))
		return 0;

	/*
	 * If we asked for subsystems (or explicitly for no
	 * subsystems) then they must match
	 */
	if ((opts->subsys_bits || opts->none)
	    && (opts->subsys_bits != root->subsys_bits))
		return 0;

	return 1;
}