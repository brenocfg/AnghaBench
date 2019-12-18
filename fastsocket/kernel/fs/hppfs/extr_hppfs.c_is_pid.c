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
struct super_block {scalar_t__ s_root; } ;
struct TYPE_2__ {int len; int /*<<< orphan*/ * name; } ;
struct dentry {scalar_t__ d_parent; TYPE_1__ d_name; struct super_block* d_sb; } ;

/* Variables and functions */
 int /*<<< orphan*/  isdigit (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int is_pid(struct dentry *dentry)
{
	struct super_block *sb;
	int i;

	sb = dentry->d_sb;
	if (dentry->d_parent != sb->s_root)
		return 0;

	for (i = 0; i < dentry->d_name.len; i++) {
		if (!isdigit(dentry->d_name.name[i]))
			return 0;
	}
	return 1;
}