#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sysfs_ops {void* (* show ) (struct kobject*,int /*<<< orphan*/ ,char*) ;} ;
struct TYPE_8__ {int /*<<< orphan*/  attr; TYPE_3__* open; } ;
struct sysfs_dirent {TYPE_4__ s_attr; TYPE_2__* s_parent; } ;
struct sysfs_buffer {char* page; void* count; scalar_t__ needs_read_fill; int /*<<< orphan*/  event; struct sysfs_ops* ops; } ;
struct kobject {int dummy; } ;
struct dentry {struct sysfs_dirent* d_fsdata; } ;
typedef  void* ssize_t ;
struct TYPE_7__ {int /*<<< orphan*/  event; } ;
struct TYPE_5__ {struct kobject* kobj; } ;
struct TYPE_6__ {TYPE_1__ s_dir; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 void* PAGE_SIZE ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 scalar_t__ get_zeroed_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_symbol (char*,unsigned long) ; 
 void* stub1 (struct kobject*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  sysfs_get_active_two (struct sysfs_dirent*) ; 
 int /*<<< orphan*/  sysfs_put_active_two (struct sysfs_dirent*) ; 

__attribute__((used)) static int fill_read_buffer(struct dentry * dentry, struct sysfs_buffer * buffer)
{
	struct sysfs_dirent *attr_sd = dentry->d_fsdata;
	struct kobject *kobj = attr_sd->s_parent->s_dir.kobj;
	const struct sysfs_ops * ops = buffer->ops;
	int ret = 0;
	ssize_t count;

	if (!buffer->page)
		buffer->page = (char *) get_zeroed_page(GFP_KERNEL);
	if (!buffer->page)
		return -ENOMEM;

	/* need attr_sd for attr and ops, its parent for kobj */
	if (!sysfs_get_active_two(attr_sd))
		return -ENODEV;

	buffer->event = atomic_read(&attr_sd->s_attr.open->event);
	count = ops->show(kobj, attr_sd->s_attr.attr, buffer->page);

	sysfs_put_active_two(attr_sd);

	/*
	 * The code works fine with PAGE_SIZE return but it's likely to
	 * indicate truncated result or overflow in normal use cases.
	 */
	if (count >= (ssize_t)PAGE_SIZE) {
		print_symbol("fill_read_buffer: %s returned bad count\n",
			(unsigned long)ops->show);
		/* Try to struggle along */
		count = PAGE_SIZE - 1;
	}
	if (count >= 0) {
		buffer->needs_read_fill = 0;
		buffer->count = count;
	} else {
		ret = count;
	}
	return ret;
}