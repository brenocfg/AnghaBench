#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int u32 ;
struct gfs2_sbd {TYPE_2__* sd_jdesc; int /*<<< orphan*/  sd_vfs; } ;
struct gfs2_log_header_host {unsigned int lh_blkno; scalar_t__ lh_sequence; } ;
struct TYPE_4__ {void* mh_jid; void* mh_format; void* __pad0; void* mh_type; void* mh_magic; } ;
struct gfs2_log_header {void* lh_hash; void* lh_blkno; void* lh_flags; void* lh_sequence; TYPE_1__ lh_header; } ;
struct gfs2_jdesc {int /*<<< orphan*/  jd_inode; } ;
struct TYPE_6__ {int i_blkbits; } ;
struct gfs2_inode {TYPE_3__ i_inode; } ;
struct buffer_head {int b_size; struct gfs2_log_header* b_data; int /*<<< orphan*/  b_blocknr; int /*<<< orphan*/  b_state; } ;
struct TYPE_5__ {unsigned int jd_jid; } ;

/* Variables and functions */
 int EIO ; 
 unsigned int GFS2_FORMAT_LH ; 
 struct gfs2_inode* GFS2_I (int /*<<< orphan*/ ) ; 
 unsigned int GFS2_LOG_HEAD_UNMOUNT ; 
 unsigned int GFS2_MAGIC ; 
 unsigned int GFS2_METATYPE_LH ; 
 struct gfs2_sbd* GFS2_SB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  clear_buffer_dirty (struct buffer_head*) ; 
 void* cpu_to_be32 (unsigned int) ; 
 void* cpu_to_be64 (scalar_t__) ; 
 int gfs2_block_map (TYPE_3__*,unsigned int,struct buffer_head*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gfs2_consist_inode (struct gfs2_inode*) ; 
 unsigned int gfs2_disk_hash (char const*,int) ; 
 int /*<<< orphan*/  gfs2_io_error_bh (struct gfs2_sbd*,struct buffer_head*) ; 
 int /*<<< orphan*/  gfs2_replay_incr_blk (struct gfs2_sbd*,unsigned int*) ; 
 int /*<<< orphan*/  lock_buffer (struct buffer_head*) ; 
 int /*<<< orphan*/  memset (struct gfs2_log_header*,int /*<<< orphan*/ ,int) ; 
 struct buffer_head* sb_getblk (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_buffer_dirty (struct buffer_head*) ; 
 int /*<<< orphan*/  set_buffer_uptodate (struct buffer_head*) ; 
 scalar_t__ sync_dirty_buffer (struct buffer_head*) ; 
 int /*<<< orphan*/  unlock_buffer (struct buffer_head*) ; 

__attribute__((used)) static int clean_journal(struct gfs2_jdesc *jd, struct gfs2_log_header_host *head)
{
	struct gfs2_inode *ip = GFS2_I(jd->jd_inode);
	struct gfs2_sbd *sdp = GFS2_SB(jd->jd_inode);
	unsigned int lblock;
	struct gfs2_log_header *lh;
	u32 hash;
	struct buffer_head *bh;
	int error;
	struct buffer_head bh_map = { .b_state = 0, .b_blocknr = 0 };

	lblock = head->lh_blkno;
	gfs2_replay_incr_blk(sdp, &lblock);
	bh_map.b_size = 1 << ip->i_inode.i_blkbits;
	error = gfs2_block_map(&ip->i_inode, lblock, &bh_map, 0);
	if (error)
		return error;
	if (!bh_map.b_blocknr) {
		gfs2_consist_inode(ip);
		return -EIO;
	}

	bh = sb_getblk(sdp->sd_vfs, bh_map.b_blocknr);
	lock_buffer(bh);
	memset(bh->b_data, 0, bh->b_size);
	set_buffer_uptodate(bh);
	clear_buffer_dirty(bh);
	unlock_buffer(bh);

	lh = (struct gfs2_log_header *)bh->b_data;
	memset(lh, 0, sizeof(struct gfs2_log_header));
	lh->lh_header.mh_magic = cpu_to_be32(GFS2_MAGIC);
	lh->lh_header.mh_type = cpu_to_be32(GFS2_METATYPE_LH);
	lh->lh_header.__pad0 = cpu_to_be64(0);
	lh->lh_header.mh_format = cpu_to_be32(GFS2_FORMAT_LH);
	lh->lh_header.mh_jid = cpu_to_be32(sdp->sd_jdesc->jd_jid);
	lh->lh_sequence = cpu_to_be64(head->lh_sequence + 1);
	lh->lh_flags = cpu_to_be32(GFS2_LOG_HEAD_UNMOUNT);
	lh->lh_blkno = cpu_to_be32(lblock);
	hash = gfs2_disk_hash((const char *)lh, sizeof(struct gfs2_log_header));
	lh->lh_hash = cpu_to_be32(hash);

	set_buffer_dirty(bh);
	if (sync_dirty_buffer(bh))
		gfs2_io_error_bh(sdp, bh);
	brelse(bh);

	return error;
}