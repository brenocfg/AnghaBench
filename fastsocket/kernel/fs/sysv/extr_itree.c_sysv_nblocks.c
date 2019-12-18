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
struct sysv_sb_info {int s_ind_per_block_bits; } ;
struct super_block {int s_blocksize; int s_blocksize_bits; } ;
typedef  int loff_t ;

/* Variables and functions */
 unsigned int DEPTH ; 
 unsigned int DIRECT ; 
 struct sysv_sb_info* SYSV_SB (struct super_block*) ; 

__attribute__((used)) static unsigned sysv_nblocks(struct super_block *s, loff_t size)
{
	struct sysv_sb_info *sbi = SYSV_SB(s);
	int ptrs_bits = sbi->s_ind_per_block_bits;
	unsigned blocks, res, direct = DIRECT, i = DEPTH;
	blocks = (size + s->s_blocksize - 1) >> s->s_blocksize_bits;
	res = blocks;
	while (--i && blocks > direct) {
		blocks = ((blocks - direct - 1) >> ptrs_bits) + 1;
		res += blocks;
		direct = 1;
	}
	return blocks;
}