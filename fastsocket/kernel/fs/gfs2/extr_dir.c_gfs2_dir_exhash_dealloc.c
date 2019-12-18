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
typedef  size_t u32 ;
struct gfs2_leaf {int /*<<< orphan*/  lf_depth; } ;
struct gfs2_inode {int i_depth; } ;
struct buffer_head {scalar_t__ b_data; } ;
typedef  int /*<<< orphan*/  __be64 ;

/* Variables and functions */
 int EIO ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int be16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ be64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int get_leaf (struct gfs2_inode*,scalar_t__,struct buffer_head**) ; 
 int /*<<< orphan*/  gfs2_consist_inode (struct gfs2_inode*) ; 
 int /*<<< orphan*/ * gfs2_dir_get_hash_table (struct gfs2_inode*) ; 
 int leaf_dealloc (struct gfs2_inode*,size_t,size_t,scalar_t__) ; 

int gfs2_dir_exhash_dealloc(struct gfs2_inode *dip)
{
	struct buffer_head *bh;
	struct gfs2_leaf *leaf;
	u32 hsize, len;
	u32 index = 0, next_index;
	__be64 *lp;
	u64 leaf_no;
	int error = 0, last;

	hsize = 1 << dip->i_depth;

	lp = gfs2_dir_get_hash_table(dip);
	if (IS_ERR(lp))
		return PTR_ERR(lp);

	while (index < hsize) {
		leaf_no = be64_to_cpu(lp[index]);
		if (leaf_no) {
			error = get_leaf(dip, leaf_no, &bh);
			if (error)
				goto out;
			leaf = (struct gfs2_leaf *)bh->b_data;
			len = 1 << (dip->i_depth - be16_to_cpu(leaf->lf_depth));

			next_index = (index & ~(len - 1)) + len;
			last = ((next_index >= hsize) ? 1 : 0);
			error = leaf_dealloc(dip, index, len, leaf_no);
			brelse(bh);
			if (error)
				goto out;
			index = next_index;
		} else
			index++;
	}

	if (index != hsize) {
		gfs2_consist_inode(dip);
		error = -EIO;
	}

out:

	return error;
}