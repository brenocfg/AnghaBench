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
typedef  scalar_t__ u16 ;
struct qnx4_xblk {int xblk_num_xtnts; int /*<<< orphan*/  xblk_next_xblk; TYPE_2__* xblk_xtnts; int /*<<< orphan*/  xblk_signature; } ;
struct TYPE_3__ {int /*<<< orphan*/  xtnt_size; int /*<<< orphan*/  xtnt_blk; } ;
struct qnx4_inode_entry {int /*<<< orphan*/  i_xblk; TYPE_1__ di_first_xtnt; int /*<<< orphan*/  di_xblk; int /*<<< orphan*/  di_num_xtnts; } ;
struct inode {int /*<<< orphan*/  i_ino; int /*<<< orphan*/  i_sb; } ;
struct buffer_head {scalar_t__ b_data; } ;
struct TYPE_4__ {int /*<<< orphan*/  xtnt_size; int /*<<< orphan*/  xtnt_blk; } ;

/* Variables and functions */
 unsigned long EIO ; 
 int /*<<< orphan*/  QNX4DEBUG (char*) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 
 long le32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,char*,int) ; 
 struct qnx4_inode_entry* qnx4_raw_inode (struct inode*) ; 
 struct buffer_head* sb_bread (int /*<<< orphan*/ ,long) ; 

unsigned long qnx4_block_map( struct inode *inode, long iblock )
{
	int ix;
	long offset, i_xblk;
	unsigned long block = 0;
	struct buffer_head *bh = NULL;
	struct qnx4_xblk *xblk = NULL;
	struct qnx4_inode_entry *qnx4_inode = qnx4_raw_inode(inode);
	u16 nxtnt = le16_to_cpu(qnx4_inode->di_num_xtnts);

	if ( iblock < le32_to_cpu(qnx4_inode->di_first_xtnt.xtnt_size) ) {
		// iblock is in the first extent. This is easy.
		block = le32_to_cpu(qnx4_inode->di_first_xtnt.xtnt_blk) + iblock - 1;
	} else {
		// iblock is beyond first extent. We have to follow the extent chain.
		i_xblk = le32_to_cpu(qnx4_inode->di_xblk);
		offset = iblock - le32_to_cpu(qnx4_inode->di_first_xtnt.xtnt_size);
		ix = 0;
		while ( --nxtnt > 0 ) {
			if ( ix == 0 ) {
				// read next xtnt block.
				bh = sb_bread(inode->i_sb, i_xblk - 1);
				if ( !bh ) {
					QNX4DEBUG(("qnx4: I/O error reading xtnt block [%ld])\n", i_xblk - 1));
					return -EIO;
				}
				xblk = (struct qnx4_xblk*)bh->b_data;
				if ( memcmp( xblk->xblk_signature, "IamXblk", 7 ) ) {
					QNX4DEBUG(("qnx4: block at %ld is not a valid xtnt\n", qnx4_inode->i_xblk));
					return -EIO;
				}
			}
			if ( offset < le32_to_cpu(xblk->xblk_xtnts[ix].xtnt_size) ) {
				// got it!
				block = le32_to_cpu(xblk->xblk_xtnts[ix].xtnt_blk) + offset - 1;
				break;
			}
			offset -= le32_to_cpu(xblk->xblk_xtnts[ix].xtnt_size);
			if ( ++ix >= xblk->xblk_num_xtnts ) {
				i_xblk = le32_to_cpu(xblk->xblk_next_xblk);
				ix = 0;
				brelse( bh );
				bh = NULL;
			}
		}
		if ( bh )
			brelse( bh );
	}

	QNX4DEBUG(("qnx4: mapping block %ld of inode %ld = %ld\n",iblock,inode->i_ino,block));
	return block;
}