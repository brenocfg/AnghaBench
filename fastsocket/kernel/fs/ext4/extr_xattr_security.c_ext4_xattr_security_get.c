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

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  EXT4_XATTR_INDEX_SECURITY ; 
 int ext4_xattr_get (struct inode*,int /*<<< orphan*/ ,char const*,void*,size_t) ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static int
ext4_xattr_security_get(struct inode *inode, const char *name,
		       void *buffer, size_t size)
{
	if (strcmp(name, "") == 0)
		return -EINVAL;
	return ext4_xattr_get(inode, EXT4_XATTR_INDEX_SECURITY, name,
			      buffer, size);
}