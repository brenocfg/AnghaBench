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
struct posix_acl {int dummy; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  GFS2_EATYPE_SYS ; 
 char* gfs2_acl_name (int) ; 
 int gfs2_xattr_set (struct inode*,int /*<<< orphan*/ ,char const*,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kmalloc (int,int /*<<< orphan*/ ) ; 
 int posix_acl_to_xattr (struct posix_acl*,char*,int) ; 
 int /*<<< orphan*/  set_cached_acl (struct inode*,int,struct posix_acl*) ; 

__attribute__((used)) static int gfs2_acl_set(struct inode *inode, int type, struct posix_acl *acl)
{
	int error;
	int len;
	char *data;
	const char *name = gfs2_acl_name(type);

	BUG_ON(name == NULL);
	len = posix_acl_to_xattr(acl, NULL, 0);
	if (len == 0)
		return 0;
	data = kmalloc(len, GFP_NOFS);
	if (data == NULL)
		return -ENOMEM;
	error = posix_acl_to_xattr(acl, data, len);
	if (error < 0)
		goto out;
	error = gfs2_xattr_set(inode, GFS2_EATYPE_SYS, name, data, len, 0);
	if (!error)
		set_cached_acl(inode, type, acl);
out:
	kfree(data);
	return error;
}