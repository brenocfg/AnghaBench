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
typedef  int /*<<< orphan*/  u64 ;
struct inode {int /*<<< orphan*/  i_version; } ;
typedef  scalar_t__ loff_t ;
typedef  int /*<<< orphan*/  filldir_t ;

/* Variables and functions */
 int EIO ; 
 scalar_t__ i_size_read (struct inode*) ; 
 int ocfs2_dir_foreach_blk (struct inode*,int /*<<< orphan*/ *,scalar_t__*,void*,int /*<<< orphan*/ ,int*) ; 

int ocfs2_dir_foreach(struct inode *inode, loff_t *f_pos, void *priv,
		      filldir_t filldir)
{
	int ret = 0, filldir_err = 0;
	u64 version = inode->i_version;

	while (*f_pos < i_size_read(inode)) {
		ret = ocfs2_dir_foreach_blk(inode, &version, f_pos, priv,
					    filldir, &filldir_err);
		if (ret || filldir_err)
			break;
	}

	if (ret > 0)
		ret = -EIO;

	return 0;
}