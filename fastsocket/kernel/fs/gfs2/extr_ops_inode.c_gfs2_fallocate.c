#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct inode {int dummy; } ;
struct TYPE_2__ {int sb_bsize; int sb_bsize_shift; } ;
struct gfs2_sbd {int sd_max_rg_data; TYPE_1__ sd_sb; } ;
struct gfs2_inode {int /*<<< orphan*/  i_gh; int /*<<< orphan*/  i_gl; } ;
struct gfs2_alloc_parms {unsigned int target; int /*<<< orphan*/  aflags; } ;
typedef  int loff_t ;

/* Variables and functions */
 int ENOSPC ; 
 long EOPNOTSUPP ; 
 int FALLOC_FL_KEEP_SIZE ; 
 struct gfs2_inode* GFS2_I (struct inode*) ; 
 struct gfs2_sbd* GFS2_SB (struct inode*) ; 
 int /*<<< orphan*/  LM_ST_EXCLUSIVE ; 
 int PAGE_CACHE_SIZE ; 
 unsigned int RES_DINODE ; 
 unsigned int RES_QUOTA ; 
 unsigned int RES_RG_HDR ; 
 unsigned int RES_STATFS ; 
 int UINT_MAX ; 
 int /*<<< orphan*/  calc_max_reserv (struct gfs2_inode*,int,int*,unsigned int*,unsigned int*) ; 
 int fallocate_chunk (struct inode*,int,int,int) ; 
 int /*<<< orphan*/  gfs2_glock_dq (int /*<<< orphan*/ *) ; 
 int gfs2_glock_nq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gfs2_holder_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gfs2_holder_uninit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gfs2_inplace_release (struct gfs2_inode*) ; 
 int gfs2_inplace_reserve (struct gfs2_inode*,struct gfs2_alloc_parms*) ; 
 scalar_t__ gfs2_is_jdata (struct gfs2_inode*) ; 
 int gfs2_quota_lock_check (struct gfs2_inode*) ; 
 int /*<<< orphan*/  gfs2_quota_unlock (struct gfs2_inode*) ; 
 unsigned int gfs2_rg_blocks (struct gfs2_inode*,unsigned int) ; 
 int gfs2_rindex_update (struct gfs2_sbd*) ; 
 int gfs2_rs_alloc (struct gfs2_inode*) ; 
 int /*<<< orphan*/  gfs2_size_hint (struct inode*,int,int) ; 
 int gfs2_trans_begin (struct gfs2_sbd*,unsigned int,int) ; 
 int /*<<< orphan*/  gfs2_trans_end (struct gfs2_sbd*) ; 
 int /*<<< orphan*/  gfs2_write_alloc_required (struct gfs2_inode*,int,int,int*) ; 
 int /*<<< orphan*/  gfs2_write_calc_reserv (struct gfs2_inode*,int,unsigned int*,unsigned int*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static long gfs2_fallocate(struct inode *inode, int mode, loff_t offset,
			   loff_t len)
{
	struct gfs2_sbd *sdp = GFS2_SB(inode);
	struct gfs2_inode *ip = GFS2_I(inode);
	struct gfs2_alloc_parms ap = { .aflags = 0, };
	int alloc_required;
	unsigned int data_blocks = 0, ind_blocks = 0, rblocks;
	loff_t bytes, max_bytes;
	int error;
	loff_t bsize_mask = ~((loff_t)sdp->sd_sb.sb_bsize - 1);
	loff_t next = (offset + len - 1) >> sdp->sd_sb.sb_bsize_shift;
	loff_t max_chunk_size = UINT_MAX & bsize_mask;
	next = (next + 1) << sdp->sd_sb.sb_bsize_shift;

	/* We only support the FALLOC_FL_KEEP_SIZE mode */
	if (mode & ~FALLOC_FL_KEEP_SIZE)
		return -EOPNOTSUPP;

	error = gfs2_rindex_update(sdp);
	if (error)
		return error;

	offset &= bsize_mask;

	len = next - offset;
	bytes = sdp->sd_max_rg_data * sdp->sd_sb.sb_bsize / 2;
	if (!bytes)
		bytes = UINT_MAX;
	bytes &= bsize_mask;
	if (bytes == 0)
		bytes = sdp->sd_sb.sb_bsize;

	error = gfs2_rs_alloc(ip);
	if (error)
		return error;

	gfs2_holder_init(ip->i_gl, LM_ST_EXCLUSIVE, 0, &ip->i_gh);
	error = gfs2_glock_nq(&ip->i_gh);
	if (unlikely(error))
		goto out_uninit;

	gfs2_size_hint(inode, offset, len);
	while (len > 0) {
		if (len < bytes)
			bytes = len;
		gfs2_write_alloc_required(ip, offset, bytes, &alloc_required);
		if (!alloc_required) {
			len -= bytes;
			offset += bytes;
			continue;
		}
		error = gfs2_quota_lock_check(ip);
		if (error)
			goto out_unlock;

retry:
		gfs2_write_calc_reserv(ip, bytes, &data_blocks, &ind_blocks);

		ap.target = data_blocks + ind_blocks;
		error = gfs2_inplace_reserve(ip, &ap);
		if (error) {
			if (error == -ENOSPC && bytes > sdp->sd_sb.sb_bsize) {
				bytes >>= 1;
				bytes &= bsize_mask;
				if (bytes == 0)
					bytes = sdp->sd_sb.sb_bsize;
				goto retry;
			}
			goto out_qunlock;
		}
		max_bytes = bytes;
		calc_max_reserv(ip, (len > max_chunk_size)? max_chunk_size: len,
				&max_bytes, &data_blocks, &ind_blocks);

		rblocks = RES_DINODE + ind_blocks + RES_STATFS + RES_QUOTA +
			  RES_RG_HDR + gfs2_rg_blocks(ip, data_blocks + ind_blocks);
		if (gfs2_is_jdata(ip))
			rblocks += data_blocks ? data_blocks : 1;

		error = gfs2_trans_begin(sdp, rblocks,
					 PAGE_CACHE_SIZE/sdp->sd_sb.sb_bsize);
		if (error)
			goto out_trans_fail;

		error = fallocate_chunk(inode, offset, max_bytes, mode);
		gfs2_trans_end(sdp);

		if (error)
			goto out_trans_fail;

		len -= max_bytes;
		offset += max_bytes;
		gfs2_inplace_release(ip);
		gfs2_quota_unlock(ip);
	}
	goto out_unlock;

out_trans_fail:
	gfs2_inplace_release(ip);
out_qunlock:
	gfs2_quota_unlock(ip);
out_unlock:
	gfs2_glock_dq(&ip->i_gh);
out_uninit:
	gfs2_holder_uninit(&ip->i_gh);
	return error;
}