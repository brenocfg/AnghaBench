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
struct NFTLrecord {unsigned int nb_blocks; unsigned int* ReplUnitTable; } ;

/* Variables and functions */
 unsigned int BLOCK_NIL ; 
 int /*<<< orphan*/  printk (char*,unsigned int) ; 

__attribute__((used)) static int calc_chain_length(struct NFTLrecord *nftl, unsigned int first_block)
{
	unsigned int length = 0, block = first_block;

	for (;;) {
		length++;
		/* avoid infinite loops, although this is guaranted not to
		   happen because of the previous checks */
		if (length >= nftl->nb_blocks) {
			printk("nftl: length too long %d !\n", length);
			break;
		}

		block = nftl->ReplUnitTable[block];
		if (!(block == BLOCK_NIL || block < nftl->nb_blocks))
			printk("incorrect ReplUnitTable[] : %d\n", block);
		if (block == BLOCK_NIL || block >= nftl->nb_blocks)
			break;
	}
	return length;
}