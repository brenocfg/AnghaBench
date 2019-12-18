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
struct kvm_stats_debugfs_item {size_t kind; scalar_t__ offset; scalar_t__ name; int /*<<< orphan*/  dentry; } ;

/* Variables and functions */
 int /*<<< orphan*/  debugfs_create_dir (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_create_file (scalar_t__,int,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 struct kvm_stats_debugfs_item* debugfs_entries ; 
 int /*<<< orphan*/  kvm_debugfs_dir ; 
 int /*<<< orphan*/ * stat_fops ; 

__attribute__((used)) static void kvm_init_debug(void)
{
	struct kvm_stats_debugfs_item *p;

	kvm_debugfs_dir = debugfs_create_dir("kvm", NULL);
	for (p = debugfs_entries; p->name; ++p)
		p->dentry = debugfs_create_file(p->name, 0444, kvm_debugfs_dir,
						(void *)(long)p->offset,
						stat_fops[p->kind]);
}