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
struct inode {int /*<<< orphan*/  i_sb; } ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  EXT4_XATTR_INDEX_USER ; 
 int /*<<< orphan*/  XATTR_USER ; 
 int ext4_xattr_get (struct inode*,int /*<<< orphan*/ ,char const*,void*,size_t) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int /*<<< orphan*/  test_opt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ext4_xattr_user_get(struct inode *inode, const char *name,
		    void *buffer, size_t size)
{
	if (strcmp(name, "") == 0)
		return -EINVAL;
	if (!test_opt(inode->i_sb, XATTR_USER))
		return -EOPNOTSUPP;
	return ext4_xattr_get(inode, EXT4_XATTR_INDEX_USER, name, buffer, size);
}