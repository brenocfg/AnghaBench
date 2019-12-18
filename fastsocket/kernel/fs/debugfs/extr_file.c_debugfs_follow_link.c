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
struct nameidata {int dummy; } ;
struct dentry {TYPE_1__* d_inode; } ;
struct TYPE_2__ {int /*<<< orphan*/  i_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  nd_set_link (struct nameidata*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void *debugfs_follow_link(struct dentry *dentry, struct nameidata *nd)
{
	nd_set_link(nd, dentry->d_inode->i_private);
	return NULL;
}