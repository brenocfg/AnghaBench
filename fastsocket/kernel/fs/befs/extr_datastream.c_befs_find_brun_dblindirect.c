#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct super_block {int dummy; } ;
struct buffer_head {scalar_t__ b_data; } ;
typedef  size_t off_t ;
struct TYPE_9__ {int block_shift; } ;
typedef  TYPE_1__ befs_sb_info ;
typedef  int /*<<< orphan*/  befs_disk_inode_addr ;
struct TYPE_11__ {int len; int start; } ;
struct TYPE_10__ {int max_indirect_range; TYPE_3__ double_indirect; } ;
typedef  TYPE_2__ befs_data_stream ;
typedef  void* befs_blocknr_t ;
typedef  TYPE_3__ befs_block_run ;

/* Variables and functions */
 size_t BEFS_DBLINDIR_BRUN_LEN ; 
 int BEFS_ERR ; 
 int BEFS_OK ; 
 TYPE_1__* BEFS_SB (struct super_block*) ; 
 struct buffer_head* befs_bread (struct super_block*,int) ; 
 int /*<<< orphan*/  befs_debug (struct super_block*,char*,void*,...) ; 
 int /*<<< orphan*/  befs_error (struct super_block*,char*,int) ; 
 int befs_iaddrs_per_block (struct super_block*) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 TYPE_3__ fsrun_to_cpu (struct super_block*,int /*<<< orphan*/ ) ; 
 int iaddr2blockno (struct super_block*,TYPE_3__*) ; 

__attribute__((used)) static int
befs_find_brun_dblindirect(struct super_block *sb,
			   befs_data_stream * data, befs_blocknr_t blockno,
			   befs_block_run * run)
{
	int dblindir_indx;
	int indir_indx;
	int offset;
	int dbl_which_block;
	int which_block;
	int dbl_block_indx;
	int block_indx;
	off_t dblindir_leftover;
	befs_blocknr_t blockno_at_run_start;
	struct buffer_head *dbl_indir_block;
	struct buffer_head *indir_block;
	befs_block_run indir_run;
	befs_disk_inode_addr *iaddr_array = NULL;
	befs_sb_info *befs_sb = BEFS_SB(sb);

	befs_blocknr_t indir_start_blk =
	    data->max_indirect_range >> befs_sb->block_shift;

	off_t dbl_indir_off = blockno - indir_start_blk;

	/* number of data blocks mapped by each of the iaddrs in
	 * the indirect block pointed to by the double indirect block
	 */
	size_t iblklen = BEFS_DBLINDIR_BRUN_LEN;

	/* number of data blocks mapped by each of the iaddrs in
	 * the double indirect block
	 */
	size_t diblklen = iblklen * befs_iaddrs_per_block(sb)
	    * BEFS_DBLINDIR_BRUN_LEN;

	befs_debug(sb, "---> befs_find_brun_dblindirect() find %lu", blockno);

	/* First, discover which of the double_indir->indir blocks
	 * contains pos. Then figure out how much of pos that
	 * accounted for. Then discover which of the iaddrs in
	 * the indirect block contains pos.
	 */

	dblindir_indx = dbl_indir_off / diblklen;
	dblindir_leftover = dbl_indir_off % diblklen;
	indir_indx = dblindir_leftover / diblklen;

	/* Read double indirect block */
	dbl_which_block = dblindir_indx / befs_iaddrs_per_block(sb);
	if (dbl_which_block > data->double_indirect.len) {
		befs_error(sb, "The double-indirect index calculated by "
			   "befs_read_brun_dblindirect(), %d, is outside the range "
			   "of the double-indirect block", dblindir_indx);
		return BEFS_ERR;
	}

	dbl_indir_block =
	    befs_bread(sb, iaddr2blockno(sb, &data->double_indirect) +
					dbl_which_block);
	if (dbl_indir_block == NULL) {
		befs_error(sb, "befs_read_brun_dblindirect() couldn't read the "
			   "double-indirect block at blockno %lu",
			   iaddr2blockno(sb,
					 &data->double_indirect) +
			   dbl_which_block);
		brelse(dbl_indir_block);
		return BEFS_ERR;
	}

	dbl_block_indx =
	    dblindir_indx - (dbl_which_block * befs_iaddrs_per_block(sb));
	iaddr_array = (befs_disk_inode_addr *) dbl_indir_block->b_data;
	indir_run = fsrun_to_cpu(sb, iaddr_array[dbl_block_indx]);
	brelse(dbl_indir_block);
	iaddr_array = NULL;

	/* Read indirect block */
	which_block = indir_indx / befs_iaddrs_per_block(sb);
	if (which_block > indir_run.len) {
		befs_error(sb, "The indirect index calculated by "
			   "befs_read_brun_dblindirect(), %d, is outside the range "
			   "of the indirect block", indir_indx);
		return BEFS_ERR;
	}

	indir_block =
	    befs_bread(sb, iaddr2blockno(sb, &indir_run) + which_block);
	if (indir_block == NULL) {
		befs_error(sb, "befs_read_brun_dblindirect() couldn't read the "
			   "indirect block at blockno %lu",
			   iaddr2blockno(sb, &indir_run) + which_block);
		brelse(indir_block);
		return BEFS_ERR;
	}

	block_indx = indir_indx - (which_block * befs_iaddrs_per_block(sb));
	iaddr_array = (befs_disk_inode_addr *) indir_block->b_data;
	*run = fsrun_to_cpu(sb, iaddr_array[block_indx]);
	brelse(indir_block);
	iaddr_array = NULL;

	blockno_at_run_start = indir_start_blk;
	blockno_at_run_start += diblklen * dblindir_indx;
	blockno_at_run_start += iblklen * indir_indx;
	offset = blockno - blockno_at_run_start;

	run->start += offset;
	run->len -= offset;

	befs_debug(sb, "Found file block %lu in double_indirect[%d][%d],"
		   " double_indirect_leftover = %lu",
		   blockno, dblindir_indx, indir_indx, dblindir_leftover);

	return BEFS_OK;
}