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
struct dentry {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/ * debugfs_create_dir (char*,int /*<<< orphan*/ *) ; 
 struct dentry* debugfs_create_file (char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct dentry* debugfs_create_u32 (char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct dentry* debugfs_create_u64 (char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * hwpoison_dir ; 
 int /*<<< orphan*/  hwpoison_filter_dev_major ; 
 int /*<<< orphan*/  hwpoison_filter_dev_minor ; 
 int /*<<< orphan*/  hwpoison_filter_enable ; 
 int /*<<< orphan*/  hwpoison_filter_flags_mask ; 
 int /*<<< orphan*/  hwpoison_filter_flags_value ; 
 int /*<<< orphan*/  hwpoison_filter_memcg ; 
 int /*<<< orphan*/  hwpoison_fops ; 
 int /*<<< orphan*/  pfn_inject_exit () ; 
 int /*<<< orphan*/  unpoison_fops ; 

__attribute__((used)) static int pfn_inject_init(void)
{
	struct dentry *dentry;

	hwpoison_dir = debugfs_create_dir("hwpoison", NULL);
	if (hwpoison_dir == NULL)
		return -ENOMEM;

	/*
	 * Note that the below poison/unpoison interfaces do not involve
	 * hardware status change, hence do not require hardware support.
	 * They are mainly for testing hwpoison in software level.
	 */
	dentry = debugfs_create_file("corrupt-pfn", 0600, hwpoison_dir,
					  NULL, &hwpoison_fops);
	if (!dentry)
		goto fail;

	dentry = debugfs_create_file("unpoison-pfn", 0600, hwpoison_dir,
				     NULL, &unpoison_fops);
	if (!dentry)
		goto fail;

	dentry = debugfs_create_u32("corrupt-filter-enable", 0600,
				    hwpoison_dir, &hwpoison_filter_enable);
	if (!dentry)
		goto fail;

	dentry = debugfs_create_u32("corrupt-filter-dev-major", 0600,
				    hwpoison_dir, &hwpoison_filter_dev_major);
	if (!dentry)
		goto fail;

	dentry = debugfs_create_u32("corrupt-filter-dev-minor", 0600,
				    hwpoison_dir, &hwpoison_filter_dev_minor);
	if (!dentry)
		goto fail;

	dentry = debugfs_create_u64("corrupt-filter-flags-mask", 0600,
				    hwpoison_dir, &hwpoison_filter_flags_mask);
	if (!dentry)
		goto fail;

	dentry = debugfs_create_u64("corrupt-filter-flags-value", 0600,
				    hwpoison_dir, &hwpoison_filter_flags_value);
	if (!dentry)
		goto fail;

#ifdef	CONFIG_CGROUP_MEM_RES_CTLR_SWAP
	dentry = debugfs_create_u64("corrupt-filter-memcg", 0600,
				    hwpoison_dir, &hwpoison_filter_memcg);
	if (!dentry)
		goto fail;
#endif

	return 0;
fail:
	pfn_inject_exit();
	return -ENOMEM;
}