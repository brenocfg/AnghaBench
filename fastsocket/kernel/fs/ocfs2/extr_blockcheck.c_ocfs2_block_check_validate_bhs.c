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
typedef  int u32 ;
typedef  int u16 ;
struct ocfs2_blockcheck_stats {int dummy; } ;
struct ocfs2_block_check {int bc_crc32e; int bc_ecc; } ;
struct buffer_head {int b_size; int /*<<< orphan*/  b_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EIO ; 
 int /*<<< orphan*/  ML_ERROR ; 
 int cpu_to_le16 (int) ; 
 int cpu_to_le32 (int) ; 
 int crc32_le (int,int /*<<< orphan*/ ,int) ; 
 int le16_to_cpu (int) ; 
 int le32_to_cpu (int) ; 
 int /*<<< orphan*/  memset (struct ocfs2_block_check*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  ocfs2_blockcheck_inc_check (struct ocfs2_blockcheck_stats*) ; 
 int /*<<< orphan*/  ocfs2_blockcheck_inc_failure (struct ocfs2_blockcheck_stats*) ; 
 int /*<<< orphan*/  ocfs2_blockcheck_inc_recover (struct ocfs2_blockcheck_stats*) ; 
 scalar_t__ ocfs2_hamming_encode (int,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  ocfs2_hamming_fix (int /*<<< orphan*/ ,int,int,int) ; 

int ocfs2_block_check_validate_bhs(struct buffer_head **bhs, int nr,
				   struct ocfs2_block_check *bc,
				   struct ocfs2_blockcheck_stats *stats)
{
	int i, rc = 0;
	struct ocfs2_block_check check;
	u32 crc, ecc, fix;

	BUG_ON(nr < 0);

	if (!nr)
		return 0;

	ocfs2_blockcheck_inc_check(stats);

	check.bc_crc32e = le32_to_cpu(bc->bc_crc32e);
	check.bc_ecc = le16_to_cpu(bc->bc_ecc);

	memset(bc, 0, sizeof(struct ocfs2_block_check));

	/* Fast path - if the crc32 validates, we're good to go */
	for (i = 0, crc = ~0; i < nr; i++)
		crc = crc32_le(crc, bhs[i]->b_data, bhs[i]->b_size);
	if (crc == check.bc_crc32e)
		goto out;

	ocfs2_blockcheck_inc_failure(stats);
	mlog(ML_ERROR,
	     "CRC32 failed: stored: %u, computed %u.  Applying ECC.\n",
	     (unsigned int)check.bc_crc32e, (unsigned int)crc);

	/* Ok, try ECC fixups */
	for (i = 0, ecc = 0; i < nr; i++) {
		/*
		 * The number of bits in a buffer is obviously b_size*8.
		 * The offset of this buffer is b_size*i, so the bit offset
		 * of this buffer is b_size*8*i.
		 */
		ecc = (u16)ocfs2_hamming_encode(ecc, bhs[i]->b_data,
						bhs[i]->b_size * 8,
						bhs[i]->b_size * 8 * i);
	}
	fix = ecc ^ check.bc_ecc;
	for (i = 0; i < nr; i++) {
		/*
		 * Try the fix against each buffer.  It will only affect
		 * one of them.
		 */
		ocfs2_hamming_fix(bhs[i]->b_data, bhs[i]->b_size * 8,
				  bhs[i]->b_size * 8 * i, fix);
	}

	/* And check the crc32 again */
	for (i = 0, crc = ~0; i < nr; i++)
		crc = crc32_le(crc, bhs[i]->b_data, bhs[i]->b_size);
	if (crc == check.bc_crc32e) {
		ocfs2_blockcheck_inc_recover(stats);
		goto out;
	}

	mlog(ML_ERROR, "Fixed CRC32 failed: stored: %u, computed %u\n",
	     (unsigned int)check.bc_crc32e, (unsigned int)crc);

	rc = -EIO;

out:
	bc->bc_crc32e = cpu_to_le32(check.bc_crc32e);
	bc->bc_ecc = cpu_to_le16(check.bc_ecc);

	return rc;
}