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
typedef  scalar_t__ u64 ;
typedef  scalar_t__ u32 ;
struct nilfs_segsum_info {scalar_t__ seg_seq; unsigned long nblocks; scalar_t__ sumbytes; unsigned long nsumblk; } ;
struct nilfs_segment_summary {int /*<<< orphan*/  ss_sumsum; int /*<<< orphan*/  ss_datasum; int /*<<< orphan*/  ss_magic; } ;
struct nilfs_sb_info {TYPE_1__* s_nilfs; TYPE_2__* s_super; } ;
struct buffer_head {scalar_t__ b_data; } ;
typedef  int /*<<< orphan*/  sector_t ;
struct TYPE_4__ {scalar_t__ s_blocksize_bits; int /*<<< orphan*/  s_blocksize; } ;
struct TYPE_3__ {unsigned long ns_blocks_per_segment; } ;

/* Variables and functions */
 scalar_t__ NILFS_SEGSUM_MAGIC ; 
 int NILFS_SEG_FAIL_CHECKSUM_FULL ; 
 int NILFS_SEG_FAIL_CHECKSUM_SEGSUM ; 
 int NILFS_SEG_FAIL_CONSISTENCY ; 
 int NILFS_SEG_FAIL_IO ; 
 int NILFS_SEG_FAIL_MAGIC ; 
 int NILFS_SEG_FAIL_SEQ ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 scalar_t__ calc_crc_cont (struct nilfs_sb_info*,struct buffer_head*,scalar_t__*,unsigned long,scalar_t__,int /*<<< orphan*/ ,unsigned long) ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 
 struct buffer_head* sb_bread (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  store_segsum_info (struct nilfs_segsum_info*,struct nilfs_segment_summary*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int
load_segment_summary(struct nilfs_sb_info *sbi, sector_t pseg_start,
		     u64 seg_seq, struct nilfs_segsum_info *ssi,
		     int full_check)
{
	struct buffer_head *bh_sum;
	struct nilfs_segment_summary *sum;
	unsigned long offset, nblock;
	u64 check_bytes;
	u32 crc, crc_sum;
	int ret = NILFS_SEG_FAIL_IO;

	bh_sum = sb_bread(sbi->s_super, pseg_start);
	if (!bh_sum)
		goto out;

	sum = (struct nilfs_segment_summary *)bh_sum->b_data;

	/* Check consistency of segment summary */
	if (le32_to_cpu(sum->ss_magic) != NILFS_SEGSUM_MAGIC) {
		ret = NILFS_SEG_FAIL_MAGIC;
		goto failed;
	}
	store_segsum_info(ssi, sum, sbi->s_super->s_blocksize);
	if (seg_seq != ssi->seg_seq) {
		ret = NILFS_SEG_FAIL_SEQ;
		goto failed;
	}
	if (full_check) {
		offset = sizeof(sum->ss_datasum);
		check_bytes =
			((u64)ssi->nblocks << sbi->s_super->s_blocksize_bits);
		nblock = ssi->nblocks;
		crc_sum = le32_to_cpu(sum->ss_datasum);
		ret = NILFS_SEG_FAIL_CHECKSUM_FULL;
	} else { /* only checks segment summary */
		offset = sizeof(sum->ss_datasum) + sizeof(sum->ss_sumsum);
		check_bytes = ssi->sumbytes;
		nblock = ssi->nsumblk;
		crc_sum = le32_to_cpu(sum->ss_sumsum);
		ret = NILFS_SEG_FAIL_CHECKSUM_SEGSUM;
	}

	if (unlikely(nblock == 0 ||
		     nblock > sbi->s_nilfs->ns_blocks_per_segment)) {
		/* This limits the number of blocks read in the CRC check */
		ret = NILFS_SEG_FAIL_CONSISTENCY;
		goto failed;
	}
	if (calc_crc_cont(sbi, bh_sum, &crc, offset, check_bytes,
			  pseg_start, nblock)) {
		ret = NILFS_SEG_FAIL_IO;
		goto failed;
	}
	if (crc == crc_sum)
		ret = 0;
 failed:
	brelse(bh_sum);
 out:
	return ret;
}