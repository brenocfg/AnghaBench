#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  kobj; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  fs_kobj ; 
 TYPE_1__* kset_create_and_add (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kset_unregister (TYPE_1__*) ; 
 int mlog_sys_init (TYPE_1__*) ; 
 int /*<<< orphan*/  o2cb_attr_group ; 
 TYPE_1__* o2cb_kset ; 
 int sysfs_create_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int sysfs_create_link (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 

int o2cb_sys_init(void)
{
	int ret;

	o2cb_kset = kset_create_and_add("o2cb", NULL, fs_kobj);
	if (!o2cb_kset)
		return -ENOMEM;

	/*
	 * Create this symlink for backwards compatibility with old
	 * versions of ocfs2-tools which look for things in /sys/o2cb.
	 */
	ret = sysfs_create_link(NULL, &o2cb_kset->kobj, "o2cb");
	if (ret)
		goto error;

	ret = sysfs_create_group(&o2cb_kset->kobj, &o2cb_attr_group);
	if (ret)
		goto error;

	ret = mlog_sys_init(o2cb_kset);
	if (ret)
		goto error;
	return 0;
error:
	kset_unregister(o2cb_kset);
	return ret;
}