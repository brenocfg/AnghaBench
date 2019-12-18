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
struct super_block {int dummy; } ;
struct inode {int /*<<< orphan*/  i_ino; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int /*<<< orphan*/  nilfs_error (struct super_block*,char const*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nilfs_handle_bmap_error(int err, const char *fname,
				   struct inode *inode, struct super_block *sb)
{
	if (err == -EINVAL) {
		nilfs_error(sb, fname, "broken bmap (inode=%lu)\n",
			    inode->i_ino);
		err = -EIO;
	}
	return err;
}