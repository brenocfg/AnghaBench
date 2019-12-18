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
struct dentry {int /*<<< orphan*/  d_inode; } ;
struct TYPE_2__ {char* i_inline; } ;

/* Variables and functions */
 TYPE_1__* JFS_IP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nd_set_link (struct nameidata*,char*) ; 

__attribute__((used)) static void *jfs_follow_link(struct dentry *dentry, struct nameidata *nd)
{
	char *s = JFS_IP(dentry->d_inode)->i_inline;
	nd_set_link(nd, s);
	return NULL;
}