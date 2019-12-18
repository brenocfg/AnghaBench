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
struct inode {int dummy; } ;
struct iattr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  generic_setattr (struct inode*,struct iattr*) ; 
 int /*<<< orphan*/  mark_inode_dirty (struct inode*) ; 

__attribute__((used)) static int __gfs2_setattr_simple(struct inode *inode, struct iattr *attr)
{
	generic_setattr(inode, attr);
	mark_inode_dirty(inode);
	return 0;
}