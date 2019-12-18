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
typedef  scalar_t__ u32 ;
typedef  scalar_t__ u16 ;
struct ocfs2_block_check {int /*<<< orphan*/  bc_ecc; int /*<<< orphan*/  bc_crc32e; } ;
struct buffer_head {int b_size; int /*<<< orphan*/  b_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ USHORT_MAX ; 
 int /*<<< orphan*/  cpu_to_le16 (scalar_t__) ; 
 int /*<<< orphan*/  cpu_to_le32 (scalar_t__) ; 
 scalar_t__ crc32_le (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (struct ocfs2_block_check*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ ocfs2_hamming_encode (scalar_t__,int /*<<< orphan*/ ,int,int) ; 

void ocfs2_block_check_compute_bhs(struct buffer_head **bhs, int nr,
				   struct ocfs2_block_check *bc)
{
	int i;
	u32 crc, ecc;

	BUG_ON(nr < 0);

	if (!nr)
		return;

	memset(bc, 0, sizeof(struct ocfs2_block_check));

	for (i = 0, crc = ~0, ecc = 0; i < nr; i++) {
		crc = crc32_le(crc, bhs[i]->b_data, bhs[i]->b_size);
		/*
		 * The number of bits in a buffer is obviously b_size*8.
		 * The offset of this buffer is b_size*i, so the bit offset
		 * of this buffer is b_size*8*i.
		 */
		ecc = (u16)ocfs2_hamming_encode(ecc, bhs[i]->b_data,
						bhs[i]->b_size * 8,
						bhs[i]->b_size * 8 * i);
	}

	/*
	 * No ecc'd ocfs2 structure is larger than 4K, so ecc will be no
	 * larger than 16 bits.
	 */
	BUG_ON(ecc > USHORT_MAX);

	bc->bc_crc32e = cpu_to_le32(crc);
	bc->bc_ecc = cpu_to_le16((u16)ecc);
}