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
 int /*<<< orphan*/  EXT3_XATTR_INDEX_USER ; 
 int /*<<< orphan*/  XATTR_USER ; 
 int ext3_xattr_set (struct inode*,int /*<<< orphan*/ ,char const*,void const*,size_t,int) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int /*<<< orphan*/  test_opt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ext3_xattr_user_set(struct inode *inode, const char *name,
		    const void *value, size_t size, int flags)
{
	if (strcmp(name, "") == 0)
		return -EINVAL;
	if (!test_opt(inode->i_sb, XATTR_USER))
		return -EOPNOTSUPP;
	return ext3_xattr_set(inode, EXT3_XATTR_INDEX_USER, name,
			      value, size, flags);
}