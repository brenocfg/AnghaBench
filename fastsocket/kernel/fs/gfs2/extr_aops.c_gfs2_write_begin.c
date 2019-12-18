#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct page {int dummy; } ;
struct TYPE_3__ {int sb_bsize; } ;
struct gfs2_sbd {TYPE_2__* sd_rindex; TYPE_1__ sd_sb; int /*<<< orphan*/  sd_statfs_inode; } ;
struct TYPE_4__ {int i_size; } ;
struct gfs2_inode {int /*<<< orphan*/  i_gh; TYPE_2__ i_inode; int /*<<< orphan*/  i_gl; } ;
struct gfs2_dinode {int dummy; } ;
struct gfs2_alloc_parms {unsigned int target; int /*<<< orphan*/  aflags; } ;
struct file {int dummy; } ;
struct address_space {int /*<<< orphan*/  host; } ;
typedef  int pgoff_t ;
typedef  int loff_t ;

/* Variables and functions */
 unsigned int AOP_FLAG_NOFS ; 
 int ENOMEM ; 
 struct gfs2_inode* GFS2_I (int /*<<< orphan*/ ) ; 
 struct gfs2_sbd* GFS2_SB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GL_NOCACHE ; 
 int /*<<< orphan*/  LM_ST_EXCLUSIVE ; 
 int PAGE_CACHE_SHIFT ; 
 int PAGE_CACHE_SIZE ; 
 int /*<<< orphan*/  PageUptodate (struct page*) ; 
 unsigned int RES_DINODE ; 
 scalar_t__ RES_QUOTA ; 
 int RES_STATFS ; 
 int block_prepare_write (struct page*,unsigned int,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gfs2_block_map ; 
 int /*<<< orphan*/  gfs2_glock_dq (int /*<<< orphan*/ *) ; 
 int gfs2_glock_nq (int /*<<< orphan*/ *) ; 
 int gfs2_glock_nq_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gfs2_holder_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gfs2_holder_uninit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gfs2_inplace_release (struct gfs2_inode*) ; 
 int gfs2_inplace_reserve (struct gfs2_inode*,struct gfs2_alloc_parms*) ; 
 scalar_t__ gfs2_is_jdata (struct gfs2_inode*) ; 
 scalar_t__ gfs2_is_stuffed (struct gfs2_inode*) ; 
 int gfs2_quota_lock_check (struct gfs2_inode*) ; 
 int /*<<< orphan*/  gfs2_quota_unlock (struct gfs2_inode*) ; 
 scalar_t__ gfs2_rg_blocks (struct gfs2_inode*,unsigned int) ; 
 int gfs2_trans_begin (struct gfs2_sbd*,unsigned int,int) ; 
 int /*<<< orphan*/  gfs2_trans_end (struct gfs2_sbd*) ; 
 int /*<<< orphan*/  gfs2_trim_blocks (TYPE_2__*) ; 
 int gfs2_unstuff_dinode (struct gfs2_inode*,struct page*) ; 
 int gfs2_write_alloc_required (struct gfs2_inode*,int,unsigned int,int*) ; 
 int /*<<< orphan*/  gfs2_write_calc_reserv (struct gfs2_inode*,unsigned int,unsigned int*,unsigned int*) ; 
 struct page* grab_cache_page_write_begin (struct address_space*,int,unsigned int) ; 
 int /*<<< orphan*/  page_cache_release (struct page*) ; 
 int stuffed_readpage (struct gfs2_inode*,struct page*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 

__attribute__((used)) static int gfs2_write_begin(struct file *file, struct address_space *mapping,
			    loff_t pos, unsigned len, unsigned flags,
			    struct page **pagep, void **fsdata)
{
	struct gfs2_inode *ip = GFS2_I(mapping->host);
	struct gfs2_sbd *sdp = GFS2_SB(mapping->host);
	struct gfs2_inode *m_ip = GFS2_I(sdp->sd_statfs_inode);
	unsigned int data_blocks = 0, ind_blocks = 0, rblocks;
	unsigned requested = 0;
	int alloc_required;
	int error = 0;
	pgoff_t index = pos >> PAGE_CACHE_SHIFT;
	unsigned from = pos & (PAGE_CACHE_SIZE - 1);
	unsigned to = from + len;
	struct page *page;

	gfs2_holder_init(ip->i_gl, LM_ST_EXCLUSIVE, 0, &ip->i_gh);
	error = gfs2_glock_nq(&ip->i_gh);
	if (unlikely(error))
		goto out_uninit;
	if (&ip->i_inode == sdp->sd_rindex) {
		error = gfs2_glock_nq_init(m_ip->i_gl, LM_ST_EXCLUSIVE,
					   GL_NOCACHE, &m_ip->i_gh);
		if (unlikely(error)) {
			gfs2_glock_dq(&ip->i_gh);
			goto out_uninit;
		}
	}

	error = gfs2_write_alloc_required(ip, pos, len, &alloc_required);
	if (error)
		goto out_unlock;

	if (alloc_required || gfs2_is_jdata(ip))
		gfs2_write_calc_reserv(ip, len, &data_blocks, &ind_blocks);

	if (alloc_required) {
		struct gfs2_alloc_parms ap = { .aflags = 0, };
		error = gfs2_quota_lock_check(ip);
		if (error)
			goto out_unlock;

		requested = data_blocks + ind_blocks;
		ap.target = requested;
		error = gfs2_inplace_reserve(ip, &ap);
		if (error)
			goto out_qunlock;
	}

	rblocks = RES_DINODE + ind_blocks;
	if (gfs2_is_jdata(ip))
		rblocks += data_blocks ? data_blocks : 1;
	if (ind_blocks || data_blocks)
		rblocks += RES_STATFS + RES_QUOTA;
	if (&ip->i_inode == sdp->sd_rindex)
		rblocks += 2 * RES_STATFS;
	if (alloc_required)
		rblocks += gfs2_rg_blocks(ip, requested);

	error = gfs2_trans_begin(sdp, rblocks,
				 PAGE_CACHE_SIZE/sdp->sd_sb.sb_bsize);
	if (error)
		goto out_trans_fail;

	error = -ENOMEM;
	flags |= AOP_FLAG_NOFS;
	page = grab_cache_page_write_begin(mapping, index, flags);
	*pagep = page;
	if (unlikely(!page))
		goto out_endtrans;

	if (gfs2_is_stuffed(ip)) {
		error = 0;
		if (pos + len > sdp->sd_sb.sb_bsize - sizeof(struct gfs2_dinode)) {
			error = gfs2_unstuff_dinode(ip, page);
			if (error == 0)
				goto prepare_write;
		} else if (!PageUptodate(page)) {
			error = stuffed_readpage(ip, page);
		}
		goto out;
	}

prepare_write:
	error = block_prepare_write(page, from, to, gfs2_block_map);
out:
	if (error == 0)
		return 0;

	unlock_page(page);
	page_cache_release(page);
	gfs2_trans_end(sdp);
	if (pos + len > ip->i_inode.i_size)
		gfs2_trim_blocks(&ip->i_inode);
	goto out_trans_fail;

out_endtrans:
	gfs2_trans_end(sdp);
out_trans_fail:
	if (alloc_required) {
		gfs2_inplace_release(ip);
out_qunlock:
		gfs2_quota_unlock(ip);
	}
out_unlock:
	if (&ip->i_inode == sdp->sd_rindex) {
		gfs2_glock_dq(&m_ip->i_gh);
		gfs2_holder_uninit(&m_ip->i_gh);
	}
	gfs2_glock_dq(&ip->i_gh);
out_uninit:
	gfs2_holder_uninit(&ip->i_gh);
	return error;
}