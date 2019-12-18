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
struct inode {int dummy; } ;
struct gfs2_sbd {int dummy; } ;
struct gfs2_leaf {scalar_t__ lf_entries; int /*<<< orphan*/  lf_next; scalar_t__ lf_depth; } ;
struct gfs2_inode {int dummy; } ;
struct gfs2_dirent {int dummy; } ;
struct dirent_gather {unsigned int offset; struct gfs2_dirent const** pdent; } ;
struct buffer_head {scalar_t__ b_blocknr; int /*<<< orphan*/  b_size; scalar_t__ b_data; } ;
typedef  int /*<<< orphan*/  filldir_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EIO ; 
 int ENOMEM ; 
 struct gfs2_inode* GFS2_I (struct inode*) ; 
 struct gfs2_sbd* GFS2_SB (struct inode*) ; 
 scalar_t__ IS_ERR (struct gfs2_dirent const*) ; 
 int PTR_ERR (struct gfs2_dirent const*) ; 
 unsigned int be16_to_cpu (scalar_t__) ; 
 scalar_t__ be64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int do_filldir_main (struct gfs2_inode*,scalar_t__*,void*,int /*<<< orphan*/ ,struct gfs2_dirent const**,unsigned int,int*) ; 
 int /*<<< orphan*/  fs_warn (struct gfs2_sbd*,char*,unsigned long long,unsigned int,unsigned int) ; 
 int get_leaf (struct gfs2_inode*,scalar_t__,struct buffer_head**) ; 
 struct buffer_head** gfs2_alloc_sort_buffer (unsigned int) ; 
 int /*<<< orphan*/  gfs2_dirent_gather ; 
 struct gfs2_dirent* gfs2_dirent_scan (struct inode*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct dirent_gather*) ; 
 int /*<<< orphan*/  gfs2_free_sort_buffer (struct buffer_head**) ; 

__attribute__((used)) static int gfs2_dir_read_leaf(struct inode *inode, u64 *offset, void *opaque,
			      filldir_t filldir, int *copied, unsigned *depth,
			      u64 leaf_no)
{
	struct gfs2_inode *ip = GFS2_I(inode);
	struct gfs2_sbd *sdp = GFS2_SB(inode);
	struct buffer_head *bh;
	struct gfs2_leaf *lf;
	unsigned entries = 0, entries2 = 0;
	unsigned leaves = 0;
	const struct gfs2_dirent **darr, *dent;
	struct dirent_gather g;
	struct buffer_head **larr;
	int leaf = 0;
	int error, i;
	u64 lfn = leaf_no;

	do {
		error = get_leaf(ip, lfn, &bh);
		if (error)
			goto out;
		lf = (struct gfs2_leaf *)bh->b_data;
		if (leaves == 0)
			*depth = be16_to_cpu(lf->lf_depth);
		entries += be16_to_cpu(lf->lf_entries);
		leaves++;
		lfn = be64_to_cpu(lf->lf_next);
		brelse(bh);
	} while(lfn);

	if (!entries)
		return 0;

	error = -ENOMEM;
	/*
	 * The extra 99 entries are not normally used, but are a buffer
	 * zone in case the number of entries in the leaf is corrupt.
	 * 99 is the maximum number of entries that can fit in a single
	 * leaf block.
	 */
	larr = gfs2_alloc_sort_buffer((leaves + entries + 99) * sizeof(void *));
	if (!larr)
		goto out;
	darr = (const struct gfs2_dirent **)(larr + leaves);
	g.pdent = darr;
	g.offset = 0;
	lfn = leaf_no;

	do {
		error = get_leaf(ip, lfn, &bh);
		if (error)
			goto out_free;
		lf = (struct gfs2_leaf *)bh->b_data;
		lfn = be64_to_cpu(lf->lf_next);
		if (lf->lf_entries) {
			entries2 += be16_to_cpu(lf->lf_entries);
			dent = gfs2_dirent_scan(inode, bh->b_data, bh->b_size,
						gfs2_dirent_gather, NULL, &g);
			error = PTR_ERR(dent);
			if (IS_ERR(dent))
				goto out_free;
			if (entries2 != g.offset) {
				fs_warn(sdp, "Number of entries corrupt in dir "
						"leaf %llu, entries2 (%u) != "
						"g.offset (%u)\n",
					(unsigned long long)bh->b_blocknr,
					entries2, g.offset);
					
				error = -EIO;
				goto out_free;
			}
			error = 0;
			larr[leaf++] = bh;
		} else {
			brelse(bh);
		}
	} while(lfn);

	BUG_ON(entries2 != entries);
	error = do_filldir_main(ip, offset, opaque, filldir, darr,
				entries, copied);
out_free:
	for(i = 0; i < leaf; i++)
		brelse(larr[i]);
	gfs2_free_sort_buffer(larr);
out:
	return error;
}