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
typedef  unsigned int u32 ;
struct inode {int dummy; } ;
struct gfs2_inode {int /*<<< orphan*/ * i_hash_cache; struct gfs2_glock* i_gl; } ;
struct gfs2_glock {int dummy; } ;
struct file_ra_state {unsigned int start; } ;
struct buffer_head {int /*<<< orphan*/  b_end_io; } ;
typedef  int /*<<< orphan*/  pgoff_t ;

/* Variables and functions */
 struct gfs2_inode* GFS2_I (struct inode*) ; 
 unsigned int MAX_RA_BLOCKS ; 
 int READA ; 
 int REQ_META ; 
 scalar_t__ be64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 scalar_t__ buffer_uptodate (struct buffer_head*) ; 
 int /*<<< orphan*/  end_buffer_read_sync ; 
 struct buffer_head* gfs2_getbuf (struct gfs2_glock*,scalar_t__,int) ; 
 unsigned int max (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  submit_bh (int,struct buffer_head*) ; 
 scalar_t__ trylock_buffer (struct buffer_head*) ; 
 int /*<<< orphan*/  unlock_buffer (struct buffer_head*) ; 

__attribute__((used)) static void gfs2_dir_readahead(struct inode *inode, unsigned hsize, u32 index,
			       struct file_ra_state *f_ra)
{
	struct gfs2_inode *ip = GFS2_I(inode);
	struct gfs2_glock *gl = ip->i_gl;
	struct buffer_head *bh;
	u64 blocknr = 0, last;
	unsigned count;

	/* First check if we've already read-ahead for the whole range. */
	if (!f_ra || index + MAX_RA_BLOCKS < f_ra->start)
		return;

	f_ra->start = max((pgoff_t)index, f_ra->start);
	for (count = 0; count < MAX_RA_BLOCKS; count++) {
		if (f_ra->start >= hsize) /* if exceeded the hash table */
			break;

		last = blocknr;
		blocknr = be64_to_cpu(ip->i_hash_cache[f_ra->start]);
		f_ra->start++;
		if (blocknr == last)
			continue;

		bh = gfs2_getbuf(gl, blocknr, 1);
		if (trylock_buffer(bh)) {
			if (buffer_uptodate(bh)) {
				unlock_buffer(bh);
				brelse(bh);
				continue;
			}
			bh->b_end_io = end_buffer_read_sync;
			submit_bh(READA | REQ_META, bh);
			continue;
		}
		brelse(bh);
	}
}