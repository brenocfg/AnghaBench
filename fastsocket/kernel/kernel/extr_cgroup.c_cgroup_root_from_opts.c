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
struct cgroupfs_root {int /*<<< orphan*/  name; int /*<<< orphan*/  release_agent_path; int /*<<< orphan*/  flags; scalar_t__ subsys_bits; } ;
struct cgroup_sb_opts {int /*<<< orphan*/  name; int /*<<< orphan*/  release_agent; int /*<<< orphan*/  flags; scalar_t__ subsys_bits; int /*<<< orphan*/  none; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct cgroupfs_root* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  init_cgroup_root (struct cgroupfs_root*) ; 
 int /*<<< orphan*/  init_root_id (struct cgroupfs_root*) ; 
 int /*<<< orphan*/  kfree (struct cgroupfs_root*) ; 
 struct cgroupfs_root* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct cgroupfs_root *cgroup_root_from_opts(struct cgroup_sb_opts *opts)
{
	struct cgroupfs_root *root;

	if (!opts->subsys_bits && !opts->none)
		return NULL;

	root = kzalloc(sizeof(*root), GFP_KERNEL);
	if (!root)
		return ERR_PTR(-ENOMEM);

	if (!init_root_id(root)) {
		kfree(root);
		return ERR_PTR(-ENOMEM);
	}
	init_cgroup_root(root);

	root->subsys_bits = opts->subsys_bits;
	root->flags = opts->flags;
	if (opts->release_agent)
		strcpy(root->release_agent_path, opts->release_agent);
	if (opts->name)
		strcpy(root->name, opts->name);
	return root;
}