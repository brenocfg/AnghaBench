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
struct inode {int /*<<< orphan*/  i_ino; int /*<<< orphan*/  i_sb; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  __ext4_error (int /*<<< orphan*/ ,char const*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mext_check_null_inode(struct inode *inode1, struct inode *inode2,
		const char *function)
{
	int ret = 0;

	if (inode1 == NULL) {
		__ext4_error(inode2->i_sb, function,
			"Both inodes should not be NULL: "
			"inode1 NULL inode2 %lu", inode2->i_ino);
		ret = -EIO;
	} else if (inode2 == NULL) {
		__ext4_error(inode1->i_sb, function,
			"Both inodes should not be NULL: "
			"inode1 %lu inode2 NULL", inode1->i_ino);
		ret = -EIO;
	}
	return ret;
}