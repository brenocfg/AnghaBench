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
typedef  int u32 ;
struct inode {int dummy; } ;
struct gfs2_inode {int i_depth; int /*<<< orphan*/ * i_hash_cache; } ;
struct file_ra_state {scalar_t__ start; } ;
typedef  int /*<<< orphan*/  filldir_t ;
typedef  int /*<<< orphan*/  __be64 ;

/* Variables and functions */
 struct gfs2_inode* GFS2_I (struct inode*) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  be64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gfs2_dir_get_hash_table (struct gfs2_inode*) ; 
 int gfs2_dir_offset2hash (int /*<<< orphan*/ ) ; 
 int gfs2_dir_read_leaf (struct inode*,int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ,int*,unsigned int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gfs2_dir_readahead (struct inode*,int,int,struct file_ra_state*) ; 

__attribute__((used)) static int dir_e_read(struct inode *inode, u64 *offset, void *opaque,
		      filldir_t filldir, struct file_ra_state *f_ra)
{
	struct gfs2_inode *dip = GFS2_I(inode);
	u32 hsize, len = 0;
	u32 hash, index;
	__be64 *lp;
	int copied = 0;
	int error = 0;
	unsigned depth = 0;

	hsize = 1 << dip->i_depth;
	hash = gfs2_dir_offset2hash(*offset);
	index = hash >> (32 - dip->i_depth);

	if (f_ra && dip->i_hash_cache == NULL)
		f_ra->start = 0;
	lp = gfs2_dir_get_hash_table(dip);
	if (IS_ERR(lp))
		return PTR_ERR(lp);

	gfs2_dir_readahead(inode, hsize, index, f_ra);

	while (index < hsize) {
		error = gfs2_dir_read_leaf(inode, offset, opaque, filldir,
					   &copied, &depth,
					   be64_to_cpu(lp[index]));
		if (error)
			break;

		len = 1 << (dip->i_depth - depth);
		index = (index & ~(len - 1)) + len;
	}

	if (error > 0)
		error = 0;
	return error;
}