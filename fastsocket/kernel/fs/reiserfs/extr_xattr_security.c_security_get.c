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
typedef  int /*<<< orphan*/  XATTR_SECURITY_PREFIX ;

/* Variables and functions */
 int EINVAL ; 
 int EPERM ; 
 scalar_t__ IS_PRIVATE (struct inode*) ; 
 int reiserfs_xattr_get (struct inode*,char const*,void*,size_t) ; 
 int strlen (char const*) ; 

__attribute__((used)) static int
security_get(struct inode *inode, const char *name, void *buffer, size_t size)
{
	if (strlen(name) < sizeof(XATTR_SECURITY_PREFIX))
		return -EINVAL;

	if (IS_PRIVATE(inode))
		return -EPERM;

	return reiserfs_xattr_get(inode, name, buffer, size);
}