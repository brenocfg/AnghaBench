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
typedef  scalar_t__ u64 ;
struct inode {scalar_t__ i_size; int /*<<< orphan*/  i_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  GFS2_I (struct inode*) ; 
 int /*<<< orphan*/  S_ISREG (int /*<<< orphan*/ ) ; 
 int do_grow (struct inode*,scalar_t__) ; 
 int do_shrink (struct inode*,scalar_t__,scalar_t__) ; 
 int get_write_access (struct inode*) ; 
 int gfs2_rs_alloc (int /*<<< orphan*/ ) ; 
 int inode_newsize_ok (struct inode*,scalar_t__) ; 
 int /*<<< orphan*/  put_write_access (struct inode*) ; 

int gfs2_setattr_size(struct inode *inode, u64 newsize)
{
	int ret;
	u64 oldsize;

	BUG_ON(!S_ISREG(inode->i_mode));

	ret = inode_newsize_ok(inode, newsize);
	if (ret)
		return ret;

	ret = get_write_access(inode);
	if (ret)
		return ret;

	ret = gfs2_rs_alloc(GFS2_I(inode));
	if (ret)
		goto out;

	oldsize = inode->i_size;
	if (newsize >= oldsize) {
		ret = do_grow(inode, newsize);
		goto out;
	}

	ret = do_shrink(inode, oldsize, newsize);
out:
	put_write_access(inode);
	return ret;
}