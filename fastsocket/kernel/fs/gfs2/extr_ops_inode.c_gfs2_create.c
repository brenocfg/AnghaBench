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
struct nameidata {int flags; } ;
struct inode {int dummy; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int LOOKUP_EXCL ; 
 int S_IFREG ; 
 int gfs2_create_inode (struct inode*,struct dentry*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int gfs2_create(struct inode *dir, struct dentry *dentry,
		       int mode, struct nameidata *nd)
{
	int excl = 0;
	if (nd && (nd->flags & LOOKUP_EXCL))
		excl = 1;
	return gfs2_create_inode(dir, dentry, S_IFREG | mode, 0, NULL, 0, excl);
}