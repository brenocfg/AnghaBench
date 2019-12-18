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
struct super_block {int /*<<< orphan*/ * s_op; int /*<<< orphan*/  s_magic; int /*<<< orphan*/  s_blocksize_bits; int /*<<< orphan*/  s_blocksize; TYPE_1__* s_fs_info; } ;
struct cgroup_sb_opts {TYPE_1__* new_root; int /*<<< orphan*/  none; int /*<<< orphan*/  subsys_bits; } ;
struct TYPE_2__ {struct super_block* sb; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  CGROUP_SUPER_MAGIC ; 
 int EINVAL ; 
 int /*<<< orphan*/  PAGE_CACHE_SHIFT ; 
 int /*<<< orphan*/  PAGE_CACHE_SIZE ; 
 int /*<<< orphan*/  cgroup_ops ; 
 int set_anon_super (struct super_block*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cgroup_set_super(struct super_block *sb, void *data)
{
	int ret;
	struct cgroup_sb_opts *opts = data;

	/* If we don't have a new root, we can't set up a new sb */
	if (!opts->new_root)
		return -EINVAL;

	BUG_ON(!opts->subsys_bits && !opts->none);

	ret = set_anon_super(sb, NULL);
	if (ret)
		return ret;

	sb->s_fs_info = opts->new_root;
	opts->new_root->sb = sb;

	sb->s_blocksize = PAGE_CACHE_SIZE;
	sb->s_blocksize_bits = PAGE_CACHE_SHIFT;
	sb->s_magic = CGROUP_SUPER_MAGIC;
	sb->s_op = &cgroup_ops;

	return 0;
}